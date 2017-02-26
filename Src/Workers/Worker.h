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
    void databaseConnectionError(const QString &info);
    void finishedProcessing(const QString &file);

private:
    struct DatabaseConnectionConfig
    {
        QString hostName;
        QString databaseName;
        int portNumber;
        QString userName;
        QString password;
    } mDatabaseConnectionConfig;

    void processOneFile(const QString &filePath);
};

}
}

#endif // WORKER_H
