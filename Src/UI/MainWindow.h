#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Parsey {
namespace UI {

class FilesListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    void arrangeWidgets();
    void handleAddFilesActionTriggered();
    void handleRemoveSelectedActionTriggered();

    QAction *mAddFilesAction;
    QAction *mRemoveSelectedFilesAction;
    FilesListWidget *mFilesList;
};

}
}

#endif // MAINWINDOW_H
