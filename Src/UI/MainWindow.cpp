#include "MainWindow.h"

#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>


namespace Parsey {
namespace UI {

static const QSize START_WINDOW_SIZE(600, 600);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    arrangeWidgets();
    resize(START_WINDOW_SIZE);
}

void MainWindow::arrangeWidgets()
{
    mAddFilesAction = new QAction(QIcon(":/Icons/Icons/add_file.png"), "Add files");
    mRemoveSelectedFilesAction = new QAction(QIcon(":/Icons/Icons/remove_file.png"), "Remove selected");

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
}

}
}
