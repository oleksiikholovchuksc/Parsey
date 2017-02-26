#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <memory>

namespace Parsey {
    namespace UI {
        class MainWindow;
    }

    namespace Model {
        class FilesModel;
    }

    namespace Workers {
        class Worker;
    }
}

namespace Parsey {
namespace Controller {

class AppController : public QObject
{
    Q_OBJECT

public:
    AppController();
    ~AppController();

    void run();

private:
    void onFilesAdditionRequest(const QStringList &files);
    void onFilesRemovalRequest(const std::vector<int> &rowsToRemove);
    void onProcessingStartRequest();
    void onFileProcessingFinished(const QString &file);

    std::unique_ptr<UI::MainWindow> mMainWindow;
    std::unique_ptr<Model::FilesModel> mFilesModel;
    std::unique_ptr<Workers::Worker> mWorker;
};

}
}

#endif // APPCONTROLLER_H
