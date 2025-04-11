#include "pch.h"

#include <filesystem>
#include <fstream>

#include "QuestForGlory1Strategy.h"

std::wstring QuestForGlory1Strategy::GetFileMask() const
{
    return L"qfg1vga.*";
}

std::wstring QuestForGlory1Strategy::GetFileToSave(const std::wstring& path, const std::wstring& filename) const
{
    std::filesystem::path filepath(path);
    filepath /= filename;

#define BINARY
#ifdef BINARY
    constexpr auto buffersize(2048);

    std::wifstream input(filepath.wstring(), std::ios::binary);
    if (!input.is_open())
        throw std::runtime_error("Error opening file " + filepath.string());

    wchar_t line[buffersize];
    while (input.read(line, buffersize)) {
        std::wstring wline(line);
        if (wline.find(L"Begin") != std::wstring::npos)
            break;
    }


#else
    std::wifstream input(filepath.wstring());
    if (!input.is_open())
        throw std::runtime_error("Error opening file " + filepath.string());

    std::wstring line;
    while (std::getline(input, line))
        if (line.find(L"Begin") != std::wstring::npos)
            break;
#endif
    return std::wstring();
}
