#pragma once

#include <oslib/oslib.h>
#include <string>
#include <unordered_map>

namespace engine::assets {

/// Owns every loaded resource (images, sounds).
/// Caches by path so the same asset is never loaded twice.
class AssetManager {
public:
    AssetManager();
    ~AssetManager();

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    OSL_IMAGE* loadImage(const std::string& path);
    OSL_SOUND* loadSound(const std::string& path);
    void       unloadAll();

private:
    std::unordered_map<std::string, OSL_IMAGE*> m_images;
    std::unordered_map<std::string, OSL_SOUND*> m_sounds;
};

} // namespace engine::assets
