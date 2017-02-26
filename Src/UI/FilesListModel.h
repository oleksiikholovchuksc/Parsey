#ifndef FILESLISTMODEL_H
#define FILESLISTMODEL_H

#include <QAbstractListModel>
#include <vector>

namespace Parsey {
namespace UI {

class FilesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    FilesListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void addFiles(const QStringList &files);
    void removeFiles(const std::vector<int> &indices);

private:
    struct ItemInfo
    {
        ItemInfo(const QString &filename_, bool wasProcessed_)
            : filename(filename_), wasProcessed(wasProcessed_)
        { }

        QString filename;
        bool wasProcessed = false;
    };

    std::vector<ItemInfo> mItems;
};

}
}

#endif // FILESLISTMODEL_H
