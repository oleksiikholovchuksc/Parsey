#include "FilesListWidget.h"

#include "UI/FilesListModel.h"

namespace Parsey {
namespace UI {

FilesListWidget::FilesListWidget(QWidget *parent)
    : QListView(parent)
    , mModel(new FilesListModel(this))
{
    setModel(mModel);
}

}
}
