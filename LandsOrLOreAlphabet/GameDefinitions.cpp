
#include "pch.h"

#include "GameDefinitions.h"

#include <stdexcept>

std::wstring ToString(Game game) {
	switch (game) {
	case Game::LandsOfLore:
		return _T("LandsOfLore");
	case Game::BetrayalAtKrondor:
		return _T("BetrayalAtKrondor");
	case Game::PlanescapeTorment:
		return _T("PlanescapeTorment");
	default:
		throw std::runtime_error("Unreachable code reached");
	}
}
std::optional<Game> ToType(const std::wstring& game) {
	if (game == _T("LandsOfLore"))
		return Game::LandsOfLore;
	if (game == _T("BetrayalAtKrondor"))
		return Game::BetrayalAtKrondor;
	if (game == _T("PlanescapeTorment"))
		return Game::PlanescapeTorment;
	return std::nullopt;
}
