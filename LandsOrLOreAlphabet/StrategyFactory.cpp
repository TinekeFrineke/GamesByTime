
#include "pch.h"

#include "StrategyFactory.h"

#include <stdexcept>

#include "BetrayalAtKrondorStrategy.h"
#include "LandsOfLoreStrategy.h"
#include "PlanescapeTormentStrategy.h"
#include "QuestForGlory1Strategy.h"
#include "QuestForGlory2Strategy.h"
#include "QuestForGlory3Strategy.h"
#include "QuestForGlory4Strategy.h"

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
    case Game::QuestForGlory1:
        return std::make_unique<QuestForGlory1Strategy>();
    case Game::QuestForGlory2:
        return std::make_unique<QuestForGlory2Strategy>();
    case Game::QuestForGlory3:
        return std::make_unique<QuestForGlory3Strategy>();
    case Game::QuestForGlory4:
        return std::make_unique<QuestForGlory4Strategy>();
    }

    throw std::runtime_error("CreateStrategy: Unknown game type " + std::to_string(int(type)));
}
} // namespace StrategyFactory