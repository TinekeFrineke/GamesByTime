#pragma once

#include "IStrategy.h"


class PlanescapeTormentStrategy :
    public IStrategy
{
public:
    std::vector<SaveData> ListItemsInPath(const std::wstring& path) const override;
};

