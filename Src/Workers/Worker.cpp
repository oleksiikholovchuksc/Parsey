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
    emit startedProcessing();

    for(const QString &file : files)
    {
        QtConcurrent::run(
            [this, file] ()
            {
                QSqlDatabase connection(QSqlDatabase::addDatabase(MYSQL_DRIVER_KEY));
                connection.setHostName(mDatabaseConnectionConfig.hostName);
                connection.setDatabaseName(mDatabaseConnectionConfig.databaseName);
                connection.setPort(mDatabaseConnectionConfig.portNumber);
                connection.setUserName(mDatabaseConnectionConfig.userName);
                connection.setPassword(mDatabaseConnectionConfig.password);
                if(!connection.open())
                {
                    emit databaseConnectionError(file);
                    return;
                }

                const QString fileName = QFileInfo(file).completeBaseName();

                QSqlQuery malwareClassesInsertQuery(connection);
                malwareClassesInsertQuery.prepare("INSERT INTO malware_classes(name) VALUES (:name);");
                malwareClassesInsertQuery.bindValue(":name", fileName);
                malwareClassesInsertQuery.exec();
                int malwareClassId = malwareClassesInsertQuery.lastInsertId().toInt();

                QSqlQuery malwareObjInsertQuery(connection);
                malwareObjInsertQuery.prepare(
                            "INSERT INTO malware_objects(name, date_added, malware_class_id) \
                             VALUES(:name, :date_added, :malware_class_id);");
                malwareObjInsertQuery.bindValue(":name", fileName);
                malwareObjInsertQuery.bindValue(":date_added", QDateTime::currentDateTime().date());
                malwareObjInsertQuery.bindValue(":malware_class_id", malwareClassId);
                malwareObjInsertQuery.exec();

                connection.close();
            }
        );
    }
}

}
}
