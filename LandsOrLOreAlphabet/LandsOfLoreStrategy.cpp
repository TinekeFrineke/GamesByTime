#include "pch.h"

#include "LandsOfLoreStrategy.h"

#include <filesystem>
#include <fstream>

std::wstring LandsOfLoreStrategy::GetFileMask() const
{
    return L"_SAVE*.dat";
}

std::wstring LandsOfLoreStrategy::GetFileToSave(const std::wstring& path, const std::wstring& filename) const
{
	std::filesystem::path filepath(path);
	filepath /= filename;
	std::wifstream instr(filepath.string());
	std::wstring name;
	std::getline(instr, name);

	return name;
}
