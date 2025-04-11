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

//#define BINARY
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
    return std::wstring();
#elif defined(NONBINARY)
    std::wifstream input(filepath.wstring());
    if (!input.is_open())
        throw std::runtime_error("Error opening file " + filepath.string());

    std::wstring line;
    while (std::getline(input, line))
        if (line.find(L"Begin") != std::wstring::npos)
            break;
    return std::wstring();
#else
    const auto position = filename.find(L'.');
    if (position == std::wstring::npos)
        throw std::runtime_error("Wrong filename: " + filepath.string());
    const std::wstring extension = filename.substr(position + 1);

    const int rank = std::wcstol(extension.c_str(), 0, 10);
    return std::to_wstring(rank);
#endif
}
