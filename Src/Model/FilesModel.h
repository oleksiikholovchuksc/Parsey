#ifndef FILESMODEL_H
#define FILESMODEL_H

#include <QStringList>
#include <vector>

namespace Parsey {
namespace Model {

class FilesModel
{
public:
    struct ItemData
    {
        ItemData(const QString &filename_, bool wasProcessed_) :
            filename(filename_), wasProcessed(wasProcessed_)
        { }

        ItemData(const QString &filename_) :
            ItemData(filename_, false)
        { }

        QString filename;
        bool wasProcessed;
    };

    FilesModel();

    void addFiles(const QStringList &files);
    void removeFilesWithIndices(const std::vector<int> indicesToRemove);

private:
    std::vector<ItemData> mItems;
};

}
}

#endif // FILESMODEL_H
