#include "Worker.h"

#include <QSettings>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtConcurrent>

namespace Parsey {
namespace Workers {

static const QString MYSQL_DRIVER_KEY = "QMYSQL";

static const QString INI_MYSQL_SECTION_NAME = "mysql";
static const QString INI_SERVER_KEY = "server";
static const QString INI_DATABASE_NAME = "database";
static const QString INI_PORT_NUMBER_KEY = "port";
static const QString INI_USERNAME_KEY = "user";
static const QString INI_PASSWORD_KEY = "password";

static const QString INI_WRONG_VALUE_STR = "__Wrong_Value__";
static const int INI_WRONG_VALUE_INT = -1;

Worker::Worker(const QString &dbConnectionIniFilePath)
{
    QSettings connectionSettings(dbConnectionIniFilePath, QSettings::IniFormat);
    connectionSettings.beginGroup(INI_MYSQL_SECTION_NAME);
    mDatabaseConnectionConfig.hostName = connectionSettings.value(INI_SERVER_KEY, INI_WRONG_VALUE_STR).toString();
    mDatabaseConnectionConfig.databaseName = connectionSettings.value(INI_DATABASE_NAME, INI_WRONG_VALUE_STR).toString();
    mDatabaseConnectionConfig.portNumber = connectionSettings.value(INI_PORT_NUMBER_KEY, INI_WRONG_VALUE_INT).toInt();
    mDatabaseConnectionConfig.userName = connectionSettings.value(INI_USERNAME_KEY, INI_WRONG_VALUE_STR).toString();
    mDatabaseConnectionConfig.password = connectionSettings.value(INI_PASSWORD_KEY, INI_WRONG_VALUE_STR).toString();
}

void Worker::startFilesProcessing(const QStringList &files)
{
    for(const QString &filePath : files)
    {
        processOneFile(filePath);
    }
}

void Worker::processOneFile(const QString &filePath)
{
    qDebug() << "Started processing of " << filePath;

    QSqlDatabase connection(QSqlDatabase::addDatabase(MYSQL_DRIVER_KEY));
    connection.setHostName(mDatabaseConnectionConfig.hostName);
    connection.setDatabaseName(mDatabaseConnectionConfig.databaseName);
    connection.setPort(mDatabaseConnectionConfig.portNumber);
    connection.setUserName(mDatabaseConnectionConfig.userName);
    connection.setPassword(mDatabaseConnectionConfig.password);
    if(!connection.open())
    {
        emit databaseConnectionError(filePath);
        return;
    }

    const QString className = QFileInfo(filePath).baseName();
    const QString objectName = QFileInfo(filePath).completeBaseName();

    QSqlQuery malwareClassesInsertQuery(connection);
    malwareClassesInsertQuery.prepare("INSERT INTO malware_classes(name) VALUES (:name);");
    malwareClassesInsertQuery.bindValue(":name", className);
    malwareClassesInsertQuery.exec();
    int malwareClassId = malwareClassesInsertQuery.lastInsertId().toInt();

    QSqlQuery malwareObjInsertQuery(connection);
    malwareObjInsertQuery.prepare(
                "INSERT INTO malware_objects(name, date_added, malware_class_id) \
                 VALUES(:name, :date_added, :malware_class_id);");
    malwareObjInsertQuery.bindValue(":name", objectName);
    malwareObjInsertQuery.bindValue(":date_added", QDateTime::currentDateTime().date());
    malwareObjInsertQuery.bindValue(":malware_class_id", malwareClassId);
    malwareObjInsertQuery.exec();
    int malwareObjId = malwareObjInsertQuery.lastInsertId().toInt();

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QTextStream textStream(&file);
    while(!textStream.atEnd())
    {
        const QString dataString = textStream.readLine();
        if(dataString != "API" && !dataString.startsWith('_'))
        {
            const QString functionName = dataString.split(' ').first();

            QSqlQuery searchFunctionNameQuery(connection);
            QString sqlQueryString = "SELECT id, api_name FROM api_objects WHERE api_name='%1';";
            sqlQueryString = sqlQueryString.arg(functionName);
            searchFunctionNameQuery.exec(sqlQueryString);

            int functionId = -1;
            if(searchFunctionNameQuery.next())
            {
                functionId = searchFunctionNameQuery.value("id").toInt();
            }

            if(functionId == -1)
            {
                QSqlQuery apiInsertQuery(connection);
                apiInsertQuery.prepare("INSERT INTO api_objects(api_name) VALUES (:api_name);");
                apiInsertQuery.bindValue(":api_name", functionName);
                apiInsertQuery.exec();
                functionId = apiInsertQuery.lastInsertId().toInt();
            }

            QSqlQuery malwareEventsInsertQuery(connection);
            malwareEventsInsertQuery.prepare(
                        "INSERT INTO malware_events(api_id, returned_value, malware_id) \
                         VALUES(:api_id, :returned_value, :malware_id);");
            malwareEventsInsertQuery.bindValue(":api_id", functionId);
            malwareEventsInsertQuery.bindValue(":returned_value", QString());
            malwareEventsInsertQuery.bindValue(":malware_id", malwareObjId);
            malwareEventsInsertQuery.exec();
        }
    }

    file.close();
    connection.close();

    emit finishedProcessing(filePath);
}

}
}
