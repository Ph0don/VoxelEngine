#pragma once

#include <unordered_map>
#include <vector>
#include <filesystem>
#include <functional>

namespace Vox
{

    class AssetTracker
    {
    public:
        AssetTracker();
        ~AssetTracker();

        void AddModifiedCallback(std::filesystem::path file, std::function<void()> callback);

    private:
        void TrackFileModification();

    private:
        std::unordered_map<std::filesystem::path, std::vector<std::function<void()>>> m_Callbacks;
        std::unordered_map<std::filesystem::path, std::filesystem::file_time_type> m_LastWriteTimes;
        bool m_IsTracking;

        std::thread m_TrackingThread;
    };

}