#include "FilesListModel.h"

#include <QIcon>

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

}
}
