#include "AssetTracker.h"

namespace Vox
{
    AssetTracker::AssetTracker()
        : m_IsTracking(true), m_TrackingThread(&AssetTracker::TrackFileModification, this)
    {
    }
    AssetTracker::~AssetTracker()
    {
        m_IsTracking = false;
        m_TrackingThread.join();
    }
    void AssetTracker::AddModifiedCallback(std::filesystem::path file, std::function<void()> callback)
    {
        //Check if we're already tracking file
        //If so add the write time
        if (m_Callbacks.find(file) == m_Callbacks.end())
        {
            m_LastWriteTimes[file] = std::filesystem::last_write_time(file);
        }

        m_Callbacks[file].push_back(callback);
    }
    void AssetTracker::TrackFileModification()
    {
        while (m_IsTracking)
        {
            for (auto& [file, callbacks] : m_Callbacks)
            {
                auto currentWriteTime = std::filesystem::last_write_time(file);
                if (currentWriteTime == m_LastWriteTimes[file])
                    continue;

                m_LastWriteTimes[file] = currentWriteTime;

                for (auto& callback : callbacks)
                {
                    callback();
                }
            }
        }
    }
}