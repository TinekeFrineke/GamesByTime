
#include "pch.h"

#include "StrategyFactory.h"

#include <stdexcept>

#include "BetrayalAtKrondorStrategy.h"
#include "LandsOfLoreStrategy.h"
#include "PlanescapeTormentStrategy.h"

namespace StrategyFactory
{
std::unique_ptr<IStrategy> CreateStrategy(Game type)
{
    switch (type) {
    case Game::BetrayalAtKrondor:
        return std::make_unique<BetrayalAtKrondorStrategy>();
    case Game::LandsOfLore:
        return std::make_unique<LandsOfLoreStrategy>();
    case Game::PlanescapeTorment:
        return std::make_unique<PlanescapeTormentStrategy>();
    }

    throw std::runtime_error("CreateStrategy: Unknown game type " + std::to_string(int(type)));
}
} // namespace StrategyFactory