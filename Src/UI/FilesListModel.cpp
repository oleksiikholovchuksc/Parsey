#include "FilesListModel.h"

#include <QIcon>
#include <set>
#include <QDebug>

namespace Parsey {
namespace UI {

static const QString SIMPLE_FILE_ICON = ":/Icons/Icons/file.png";
static const QString PROCESSED_FILE_ICON = ":/Icons/Icons/done_file.png";

FilesListModel::FilesListModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int FilesListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return static_cast<int>(mItems.size());
}

QVariant FilesListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= static_cast<int>(mItems.size()))
        return QVariant();

    QVariant result;

    if(role == Qt::DisplayRole)
    {
        result = QVariant(mItems[row].filename);
    }
    else if(role == Qt::DecorationRole)
    {
        if(!mItems[row].wasProcessed)
            return QVariant(QIcon(SIMPLE_FILE_ICON));
        else
            return QVariant(QIcon(PROCESSED_FILE_ICON));
    }

    return result;
}

void FilesListModel::addFiles(const QStringList &files)
{
    for(const QString &file : files)
    {
        mItems.push_back({file, false});
    }

    QModelIndex startChangeIndex(index(static_cast<int>(mItems.size())));
    QModelIndex endChangeIndex(index(static_cast<int>(mItems.size()) + files.size() - 1));
    emit dataChanged(startChangeIndex, endChangeIndex, {Qt::DisplayRole});
}

void FilesListModel::removeFiles(const std::vector<int> &indices)
{
    std::set<int> indicesSet(indices.begin(), indices.end());
    std::vector<ItemInfo> newItemList;
    for(int i = 0; i < static_cast<int>(mItems.size()); ++i)
    {
        if(indicesSet.find(i) == indicesSet.end())
            newItemList.push_back(mItems[i]);
    }
    mItems = newItemList;

    QModelIndex startChangeIndex(index(0));
    QModelIndex endChangeIndex(index(static_cast<int>(mItems.size() + indices.size()) - 1));
    emit dataChanged(startChangeIndex, endChangeIndex, {Qt::DisplayRole, Qt::DecorationRole});
}

}
}
