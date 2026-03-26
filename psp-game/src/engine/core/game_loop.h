#pragma once

#include "scene_manager.h"
#include "../input/input.h"
#include "../graphics/renderer.h"
#include "../assets/asset_manager.h"
#include "../memory/memory_manager.h"

namespace engine {

/// Top-level object. Owns all subsystems, runs the tick/draw loop.
class GameLoop {
public:
    GameLoop();
    void run();   // blocks until the game exits

    core::SceneManager&       scenes()   { return m_scenes; }
    input::Input&             input()    { return m_input; }
    graphics::Renderer&       renderer() { return m_renderer; }
    assets::AssetManager&     assets()   { return m_assets; }
    memory::MemoryManager&    memory()   { return m_memory; }

private:
    bool m_running;

    core::SceneManager    m_scenes;
    input::Input          m_input;
    graphics::Renderer    m_renderer;
    assets::AssetManager  m_assets;
    memory::MemoryManager m_memory;
};

} // namespace engine
