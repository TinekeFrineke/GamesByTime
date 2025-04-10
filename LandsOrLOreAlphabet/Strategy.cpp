#include "pch.h"

#include <algorithm>

#include "Strategy.h"

#include "StrategyUtilities.h"

std::vector<IStrategy::SaveData> Strategy::ListItemsInPath(const std::wstring& path) const
{
    auto files(StrategyUtilities::FilesInPath(path, GetFileMask()));

    std::sort(files.begin(), files.end(), [](const WIN32_FIND_DATA& lhs, const WIN32_FIND_DATA& rhs)
              { return lhs.ftLastWriteTime < rhs.ftLastWriteTime; });

    std::vector<IStrategy::SaveData> data;
    for (auto file : files)
        data.push_back(std::make_pair<>(file.cFileName, GetFileToSave(path, file.cFileName)));
    return data;
}
