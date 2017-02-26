#ifndef WORKER_H
#define WORKER_H

#include <QObject>

namespace Parsey {
namespace Workers {

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(const QString &dbConnectionIniFilePath);

    void startFilesProcessing(const QStringList &files);

signals:
    void startedProcessing();

private:
    struct DatabaseConnectionConfig
    {
        QString hostName;
        QString databaseName;
        int portNumber;
        QString userName;
        QString password;
    } mDatabaseConnectionConfig;
};

}
}

#endif // WORKER_H
