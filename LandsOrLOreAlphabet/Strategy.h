#pragma once

#include <string>
#include <vector>

#include "IStrategy.h"

class Strategy
    : public IStrategy
{
public:
    virtual ~Strategy() = default;
    std::vector<SaveData> ListItemsInPath(const std::wstring& path) const override;

    virtual std::wstring GetFileMask() const = 0;
    virtual std::wstring GetFileToSave(const std::wstring& path, const std::wstring& filename) const = 0;
};

