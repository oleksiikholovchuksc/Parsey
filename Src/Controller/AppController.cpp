#include "AppController.h"

#include "UI/MainWindow.h"
#include "Model/FilesModel.h"

namespace Parsey {
namespace Controller {

AppController::AppController()
    : mMainWindow(new UI::MainWindow())
    , mFilesModel(new Model::FilesModel())
{
    connect(mMainWindow.get(), &UI::MainWindow::filesAdditionRequested,
            this, &AppController::onFilesAdditionRequest);

    connect(mMainWindow.get(), &UI::MainWindow::filesRemovalRequested,
            this, &AppController::onFilesRemovalRequest);
}

AppController::~AppController()
{

}

void AppController::run()
{
    mMainWindow->show();
}

void AppController::onFilesAdditionRequest(const QStringList &files)
{
    mFilesModel->addFiles(files);
    mMainWindow->addFiles(files);
}

void AppController::onFilesRemovalRequest(const std::vector<int> &rowsToRemove)
{
    mFilesModel->removeFilesWithIndices(rowsToRemove);
    mMainWindow->removeFiles(rowsToRemove);
}

}
}
