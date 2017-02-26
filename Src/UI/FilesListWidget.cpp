#include "FilesListWidget.h"

#include "UI/FilesListModel.h"

namespace Parsey {
namespace UI {

FilesListWidget::FilesListWidget(QWidget *parent)
    : QListView(parent)
    , mModel(new FilesListModel(this))
{
    setModel(mModel);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void FilesListWidget::addFiles(const QStringList &files)
{
    mModel->addFiles(files);
}

void FilesListWidget::removeFiles(const std::vector<int> &indices)
{
    mModel->removeFiles(indices);
    selectionModel()->clearSelection();
}

std::vector<int> FilesListWidget::getSelectedRows()
{
    const QModelIndexList selectedIndices = selectionModel()->selectedRows();
    std::vector<int> result;
    result.reserve(selectedIndices.size());
    for(const QModelIndex &index : selectedIndices)
    {
        result.push_back(index.row());
    }

    return result;
}

bool FilesListWidget::isEmpty()
{
    return mModel->rowCount(QModelIndex()) == 0;
}

}
}
