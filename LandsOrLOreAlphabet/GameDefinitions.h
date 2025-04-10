#pragma once

#include <optional>
#include <string>

enum class Game {
	LandsOfLore,
	BetrayalAtKrondor,
	PlanescapeTorment
};

std::wstring ToString(Game game);
std::optional<Game> ToType(const std::wstring& game);

