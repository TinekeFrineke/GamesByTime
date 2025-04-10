#pragma once

#include <string>
#include <vector>

class IStrategy
{
public:
    using FileName = std::wstring;
    using SaveName = std::wstring;
    using SaveData = std::pair<FileName, SaveName>;

    virtual ~IStrategy() = default;
    virtual std::vector<SaveData> ListItemsInPath(const std::wstring& path) const = 0;
};

