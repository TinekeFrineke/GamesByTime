#pragma once

#include <string>
#include <vector>
#include <Windows.h>

struct _FILETIME;
typedef struct _FILETIME FILETIME;

struct _WIN32_FIND_DATAW;
typedef struct _WIN32_FIND_DATAW WIN32_FIND_DATAW;
typedef WIN32_FIND_DATAW WIN32_FIND_DATA;


namespace StrategyUtilities
{

//using SaveNameDateRetriever = std::function < std::pair<FILETIME, std::wstring>(const std::wstring&, const WIN32_FIND_DATA&)>;

std::vector<WIN32_FIND_DATA> FilesInPath(const std::wstring& path, const std::wstring& fileMask);
std::vector<WIN32_FIND_DATA> DirectoriesInPath(const std::wstring& path);

}  // namespace StrategyUtilities

bool operator<(const FILETIME& f1, const FILETIME& f2);

