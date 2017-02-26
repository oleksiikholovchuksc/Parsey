#include "MainWindow.h"

#include "FilesListWidget.h"

#include <QVBoxLayout>
#include <QProgressBar>
#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

namespace Parsey {
namespace UI {

static const QSize START_WINDOW_SIZE(600, 600);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mAddFilesAction(new QAction(QIcon(":/Icons/Icons/add_file.png"), "Add files"))
    , mRemoveSelectedFilesAction(new QAction(QIcon(":/Icons/Icons/remove_file.png"), "Remove selected"))
    , mDoProcessingAction(new QAction(QIcon(":/Icons/Icons/process.png"), "Do processing"))
    , mFilesList(new FilesListWidget)
{
    connect(mAddFilesAction, &QAction::triggered,
            this, &MainWindow::handleAddFilesActionTriggered);

    connect(mRemoveSelectedFilesAction, &QAction::triggered,
            this, &MainWindow::handleRemoveSelectedActionTriggered);

    connect(mDoProcessingAction, &QAction::triggered,
            this, &MainWindow::processingStartRequested);

    arrangeWidgets();
    resize(START_WINDOW_SIZE);
    updateActionsAvailability();
}

void MainWindow::addFiles(const QStringList &files)
{
    mFilesList->addFiles(files);
    updateActionsAvailability();
}

void MainWindow::removeFiles(const std::vector<int> &indices)
{
    mFilesList->removeFiles(indices);
    updateActionsAvailability();
}

void MainWindow::arrangeWidgets()
{
    /* MENUBAR */
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = new QMenu("File", menuBar);
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(mAddFilesAction);
    fileMenu->addAction(mRemoveSelectedFilesAction);

    QMenu *processingMenu = new QMenu("Processing", menuBar);
    menuBar->addMenu(processingMenu);
    processingMenu->addAction(mDoProcessingAction);

    /* TOOLBAR */
    QToolBar *filesToolbar = new QToolBar();
    addToolBar(filesToolbar);
    filesToolbar->addAction(mAddFilesAction);
    filesToolbar->addAction(mRemoveSelectedFilesAction);

    QToolBar *processingToolbar = new QToolBar();
    addToolBar(processingToolbar);
    processingToolbar->addAction(mDoProcessingAction);

    /* MAIN AREA */
    QWidget *dummyCentralWidget = new QWidget();
    setCentralWidget(dummyCentralWidget);

    QVBoxLayout *vLayout = new QVBoxLayout();
    dummyCentralWidget->setLayout(vLayout);

    vLayout->addWidget(mFilesList);
}

void MainWindow::handleAddFilesActionTriggered()
{
    const auto desktopPath = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)[0];

    QStringList files
            = QFileDialog::getOpenFileNames(
                this,
                "Choose files",
                desktopPath,
                "Text files (*.txt)");

    if(!files.isEmpty())
    {
        emit filesAdditionRequested(files);
    }
}

void MainWindow::handleRemoveSelectedActionTriggered()
{
    emit filesRemovalRequested(mFilesList->getSelectedRows());
}

void MainWindow::updateActionsAvailability()
{
    bool actionsAreEnabled = !mFilesList->isEmpty();
    mRemoveSelectedFilesAction->setEnabled(actionsAreEnabled);
    mDoProcessingAction->setEnabled(actionsAreEnabled);
}

}
}
