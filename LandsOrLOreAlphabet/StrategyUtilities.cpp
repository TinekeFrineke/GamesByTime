#include "pch.h"

#include "StrategyUtilities.h"

#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <string>

bool operator<(const FILETIME& f1, const FILETIME& f2)
{
	SYSTEMTIME s1{};
	SYSTEMTIME s2{};
	FileTimeToSystemTime(&f1, &s1);
	FileTimeToSystemTime(&f2, &s2);

	if (s1.wYear < s2.wYear)
		return true;
	else if (s1.wYear > s2.wYear)
		return false;

	if (s1.wMonth < s2.wMonth)
		return true;
	else if (s1.wMonth > s2.wMonth)
		return false;

	if (s1.wDay < s2.wDay)
		return true;
	else if (s1.wDay > s2.wDay)
		return false;

	if (s1.wHour < s2.wHour)
		return true;
	else if (s1.wHour > s2.wHour)
		return false;

	if (s1.wMinute < s2.wMinute)
		return true;
	else if (s1.wMinute > s2.wMinute)
		return false;

	if (s1.wSecond < s2.wSecond)
		return true;
	else if (s1.wSecond > s2.wSecond)
		return false;

	return s1.wMilliseconds < s2.wMilliseconds;
}

namespace StrategyUtilities {

std::pair<FILETIME, std::string> RetrieveDateAndSaveName(const std::wstring& rPath, const WIN32_FIND_DATA& aData)
{
	const size_t length(rPath.length() + wcslen(aData.cFileName));
	char* path = new char[length + 1];
	sprintf_s(path, length + 1, "%S%S", rPath.c_str(), aData.cFileName);
	std::ifstream instr(path);
	delete[] path;
	std::string name;
	std::getline(instr, name);

	return std::pair<FILETIME, std::string>(aData.ftLastWriteTime, name);
}

std::vector<WIN32_FIND_DATA> FilesInPath(const std::wstring& path, const std::wstring& fileMask)
{
	std::filesystem::path gamepath(path);
	gamepath /= fileMask;

	WIN32_FIND_DATA FindFileData{};

	std::vector<WIN32_FIND_DATA> Saves;

	HANDLE hFind = FindFirstFile(gamepath.wstring().c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
		Saves.push_back(FindFileData);

	while (FindNextFile(hFind, &FindFileData) != FALSE)
		Saves.push_back(FindFileData);

	return Saves;
}

std::vector<WIN32_FIND_DATA> DirectoriesInPath(const std::wstring& path)
{
	std::filesystem::path gamepath(path);
	for (auto entry : gamepath) {
		(void)entry;
	}

	gamepath /= "*";

	WIN32_FIND_DATA FindFileData{};

	std::vector<WIN32_FIND_DATA> Saves;

	HANDLE hFind = FindFirstFile(gamepath.wstring().c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
		Saves.push_back(FindFileData);

	while (FindNextFile(hFind, &FindFileData) != FALSE)
		Saves.push_back(FindFileData);

	return Saves;
}

} // namespace StrategyUtilities