#include "FilesModel.h"

#include <set>
#include <algorithm>

namespace Parsey {
namespace Model {

FilesModel::FilesModel()
{

}

void FilesModel::addFiles(const QStringList &files)
{
    std::copy(files.begin(), files.end(), std::back_inserter(mItems));
}

void FilesModel::removeFilesWithIndices(const std::vector<int> indices)
{
    std::set<int> indicesSet(indices.begin(), indices.end());
    std::vector<ItemData> newItemList;
    for(int i = 0; i < static_cast<int>(mItems.size()); ++i)
    {
        if(indicesSet.find(i) == indicesSet.end())
            newItemList.push_back(mItems[i]);
    }
    mItems = newItemList;
}

const std::vector<FilesModel::ItemData> &FilesModel::getData() const
{
    return mItems;
}

}
}
