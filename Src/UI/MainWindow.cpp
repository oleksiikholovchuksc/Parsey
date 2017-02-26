#include "MainWindow.h"

#include "FilesListWidget.h"

#include <QVBoxLayout>
#include <QProgressBar>
#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>

namespace Parsey {
namespace UI {

static const QSize START_WINDOW_SIZE(600, 600);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mAddFilesAction(new QAction(QIcon(":/Icons/Icons/add_file.png"), "Add files"))
    , mRemoveSelectedFilesAction(new QAction(QIcon(":/Icons/Icons/remove_file.png"), "Remove selected"))
    , mFilesList(new FilesListWidget)
{
    connect(mAddFilesAction, &QAction::triggered, this, &MainWindow::handleAddFilesActionTriggered);
    connect(mRemoveSelectedFilesAction, &QAction::triggered, this, &MainWindow::handleRemoveSelectedActionTriggered);

    arrangeWidgets();
    resize(START_WINDOW_SIZE);
}

void MainWindow::arrangeWidgets()
{
    /* MENUBAR AND TOOLBAR */
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    QMenu *fileMenu = new QMenu("File", menuBar);
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(mAddFilesAction);
    fileMenu->addAction(mRemoveSelectedFilesAction);

    QToolBar *toolbar = new QToolBar();
    addToolBar(toolbar);
    toolbar->addAction(mAddFilesAction);
    toolbar->addAction(mRemoveSelectedFilesAction);

    /* MAIN AREA */
    QWidget *dummyCentralWidget = new QWidget();
    setCentralWidget(dummyCentralWidget);

    QVBoxLayout *vLayout = new QVBoxLayout();
    dummyCentralWidget->setLayout(vLayout);

    vLayout->addWidget(mFilesList);
}

void MainWindow::handleAddFilesActionTriggered()
{

}

void MainWindow::handleRemoveSelectedActionTriggered()
{

}

}
}
