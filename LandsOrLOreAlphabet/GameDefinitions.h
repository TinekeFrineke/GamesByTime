#pragma once

#include <map>
#include <optional>
#include <string>

enum class Game {
	LandsOfLore,
	BetrayalAtKrondor,
	PlanescapeTorment,
	QuestForGlory1,
	QuestForGlory2,
	QuestForGlory3,
	QuestForGlory4,
};

std::wstring ToString(Game game);
std::optional<Game> ToType(const std::wstring& game);

std::map<Game, std::wstring> allGames();

