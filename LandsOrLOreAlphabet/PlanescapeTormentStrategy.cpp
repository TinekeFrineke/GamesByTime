#include "pch.h"

#include <filesystem>
#include <fstream>

#include "PlanescapeTormentStrategy.h"
#include "StrategyUtilities.h"

namespace {
std::wstring GetSaveName(const std::filesystem::path& path)
{
    auto fileName = path.filename().string();
    auto saveName = fileName.substr(10);
    wchar_t wSaveName[100];
    swprintf(wSaveName, 100, L"%S", saveName.c_str());
    return wSaveName;
}
}

std::vector<IStrategy::SaveData> PlanescapeTormentStrategy::ListItemsInPath(const std::wstring& path) const
{
    std::filesystem::path savePath(path);

    struct SaveHelper {
        std::filesystem::path file;
        std::chrono::time_point<std::chrono::system_clock> time;
    };
    std::vector<SaveHelper> files;

    if (std::filesystem::exists(path)) {
        try {
            auto iterator = std::filesystem::directory_iterator(path);
            for (const auto& dirEntry : std::filesystem::directory_iterator(path)) {
                if (std::filesystem::is_directory(dirEntry)) {
                    auto filepath = dirEntry.path() / L"BALDUR.SAV";
                    if (!std::filesystem::exists(filepath))
                        continue;
                    if (std::filesystem::is_directory(filepath))
                        continue;

                    auto x = std::chrono::time_point<std::chrono::system_clock>(std::filesystem::last_write_time(filepath).time_since_epoch());
                    files.push_back({ dirEntry.path(), x });
                }
            }
        }
        catch (std::exception& ex) {
            ::MessageBoxA(0, ex.what(), "ERROR", MB_OK);
        }
        catch (...) {
            ::MessageBoxA(0, "Unknown Error", "ERROR", MB_OK);
        }
    }

    std::sort(files.begin(), files.end(), [](const SaveHelper& lhs, const SaveHelper& rhs)
              { return lhs.time < rhs.time; });

    std::vector<IStrategy::SaveData> data;
    for (auto file : files) {
        auto filename = GetSaveName(file.file.filename());
        data.push_back(std::make_pair<>(filename, filename));
    }
    return data;
}
