
#include "pch.h"

#include "GameDefinitions.h"

#include <map>
#include <stdexcept>


namespace {
std::map <Game, std::wstring> gamesList = {
    { Game::LandsOfLore, L"LandsOfLore" },
    { Game::BetrayalAtKrondor, L"BetrayalAtKrondor" },
    { Game::PlanescapeTorment, L"PlanescapeTorment" },
    { Game::QuestForGlory1, L"QuestForGlory1" },
    { Game::QuestForGlory2, L"QuestForGlory2" },
    { Game::QuestForGlory3, L"QuestForGlory3" },
    { Game::QuestForGlory4, L"QuestForGlory4" }
};
}


std::wstring ToString(Game game) {
    auto found = gamesList.find(game);
    if (found != gamesList.end())
        return found->second;

    throw std::runtime_error("Unreachable code reached");
}

std::optional<Game> ToType(const std::wstring& game) {
    auto found = std::find_if(gamesList.begin(), gamesList.end(), [&game] (const std::pair<Game, std::wstring>& pair) { return pair.second == game; });
    if (found != gamesList.end())
        return found->first;

    return std::nullopt;
}

std::map<Game, std::wstring> allGames()
{
    return gamesList;
}
