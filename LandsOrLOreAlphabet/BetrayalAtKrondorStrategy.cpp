#include "pch.h"
#include "BetrayalAtKrondorStrategy.h"

#include <filesystem>
#include <fstream>

std::wstring BetrayalAtKrondorStrategy::GetFileMask() const
{
    return L"SAVE*.GAM";
}

std::wstring BetrayalAtKrondorStrategy::GetFileToSave(const std::wstring& path, const std::wstring& filename) const
{
	std::filesystem::path filepath(path);
	filepath /= filename;
	std::wifstream instr(filepath.string());
	std::wstring name;
	std::getline(instr, name);

	return name;
}
