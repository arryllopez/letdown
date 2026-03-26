#include "asset_manager.h"

namespace engine::assets {

AssetManager::AssetManager() = default;

AssetManager::~AssetManager() {
    // TODO: iterate maps and oslDeleteImage / oslDeleteSound
}

OSL_IMAGE* AssetManager::loadImage(const std::string& path) {
    // TODO: check cache, load via oslLoadImageFilePNG/etc., store, return
    return nullptr;
}

OSL_SOUND* AssetManager::loadSound(const std::string& path) {
    // TODO: check cache, load via oslLoadSoundFile, store, return
    return nullptr;
}

void AssetManager::unloadAll() {
    // TODO: free every cached image and sound, clear maps
}

} // namespace engine::assets
