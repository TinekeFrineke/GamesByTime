#include "pch.h"

#include "Settings.h"

#include <filesystem>

namespace {
std::wstring InifileName()
{
    auto curpath(std::filesystem::current_path());
    auto file(curpath / _T("GamesByDate.ini"));
    return file.wstring();
}
}

Game Settings::GetGame() const
{
    TCHAR game[1024];
    GetPrivateProfileString(_T("General"), _T("Game"), _T(""), game, MAX_PATH, InifileName().c_str());
    auto gametype(ToType(game));
    if (gametype)
        return *gametype;

    return static_cast<Game>(0);
}

std::wstring Settings::GetPath(Game game) const
{
    TCHAR path[MAX_PATH];
    GetPrivateProfileString(ToString(game).c_str(), _T("Path"), _T(""), path, MAX_PATH, InifileName().c_str());
    if (wcslen(path) == 0)
        GetPrivateProfileString(L"General", _T("Path"), _T(""), path, MAX_PATH, InifileName().c_str());

    return path;
}

void Settings::SetGame(Game game)
{
    WritePrivateProfileString(_T("General"), _T("Game"), ToString(game).c_str(), InifileName().c_str());
}

void Settings::SetPath(Game game, const std::wstring& path) const
{
    WritePrivateProfileString(ToString(game).c_str(), _T("Path"), path.c_str(), InifileName().c_str());
}
