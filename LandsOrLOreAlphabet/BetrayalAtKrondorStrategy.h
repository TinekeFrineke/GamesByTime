#pragma once

#include "Strategy.h"

class BetrayalAtKrondorStrategy :
    public Strategy
{
public:
    std::wstring GetFileMask() const override;
    std::wstring GetFileToSave(const std::wstring& path, const std::wstring& filename) const override;
};

