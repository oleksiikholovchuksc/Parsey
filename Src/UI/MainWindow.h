#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Parsey {
namespace UI {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    void arrangeWidgets();

    QAction *mAddFilesAction;
    QAction *mRemoveSelectedFilesAction;
};

}
}

#endif // MAINWINDOW_H
