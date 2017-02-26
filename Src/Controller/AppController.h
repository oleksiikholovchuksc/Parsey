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

    std::unique_ptr<UI::MainWindow> mMainWindow;
    std::unique_ptr<Model::FilesModel> mFilesModel;
};

}
}

#endif // APPCONTROLLER_H
