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

    void addFiles(const QStringList &files);
    void removeFiles(const std::vector<int> &indices);

signals:
    void filesAdditionRequested(const QStringList &files);
    void filesRemovalRequested(const std::vector<int> &rowsToRemove);

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
