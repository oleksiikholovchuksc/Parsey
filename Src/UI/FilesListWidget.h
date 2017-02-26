#ifndef FILESLISTWIDGET_H
#define FILESLISTWIDGET_H

#include <QListView>

namespace Parsey {
namespace UI {

class FilesListModel;

class FilesListWidget : public QListView
{
    Q_OBJECT

public:
    FilesListWidget(QWidget *parent = 0);

private:
    FilesListModel *mModel;
};

}
}

#endif // FILESLISTWIDGET_H
