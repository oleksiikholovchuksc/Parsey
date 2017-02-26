#include "AppController.h"

#include "UI/MainWindow.h"
#include "Model/FilesModel.h"
#include "Workers/Worker.h"

namespace Parsey {
namespace Controller {

static const QString DB_CONNECTION_INI_FILE_PATH = "./db_config.ini";

AppController::AppController()
    : mMainWindow(new UI::MainWindow())
    , mFilesModel(new Model::FilesModel())
    , mWorker(new Workers::Worker(DB_CONNECTION_INI_FILE_PATH))
{
    connect(mMainWindow.get(), &UI::MainWindow::filesAdditionRequested,
            this, &AppController::onFilesAdditionRequest);

    connect(mMainWindow.get(), &UI::MainWindow::filesRemovalRequested,
            this, &AppController::onFilesRemovalRequest);

    connect(mMainWindow.get(), &UI::MainWindow::processingStartRequested,
            this, &AppController::onProcessingStartRequest);
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

void AppController::onProcessingStartRequest()
{

}

}
}
