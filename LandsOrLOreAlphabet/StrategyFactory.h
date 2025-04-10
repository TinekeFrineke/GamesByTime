#pragma once

#include <memory>

#include "GameDefinitions.h"

class IStrategy;

namespace StrategyFactory
{
std::unique_ptr<IStrategy> CreateStrategy(Game type);
} // namespace StrategyFactory