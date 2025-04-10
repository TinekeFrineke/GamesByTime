#pragma once

#include "Strategy.h"

class LandsOfLoreStrategy :
    public Strategy
{
public:

    // Returns the strings representing the file name
    std::wstring GetFileMask() const override;
    std::wstring GetFileToSave(const std::wstring& path, const std::wstring& filename) const override;
};
