#include "Worker.h"

#include <QSettings>
#include <QtSql/QSqlDatabase>
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

//    database->setHostName(serverName);
//    database->setDatabaseName(databaseName);
//    database->setPort(portNumber);
//    database->setUserName(username);
//    database->setPassword(password);

//    if(!database->open())
//    {
//        throw std::runtime_error("Couldn't connect to a database");
//    }
}

void Worker::startFilesProcessing(const QStringList &files)
{
    emit startedProcessing();
}

}
}
