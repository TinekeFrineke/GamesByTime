#pragma once

#include "Strategy.h"


class QuestForGlory1Strategy
    : public Strategy
{
    // Inherited via Strategy
    virtual std::wstring GetFileMask() const override;
    virtual std::wstring GetFileToSave(const std::wstring& path, const std::wstring& filename) const override;
};

