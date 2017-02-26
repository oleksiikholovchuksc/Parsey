#include "FilesModel.h"

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

void FilesModel::removeFilesWithIndices(const std::vector<int> indicesToRemove)
{

}

}
}
