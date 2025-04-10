#pragma once

#include <string>

#include "GameDefinitions.h"

class Settings
{
public:
    Game GetGame() const;
    std::wstring GetPath(Game game) const;

    void SetGame(Game game);
    void SetPath(Game game, const std::wstring& path) const;

private:
};

