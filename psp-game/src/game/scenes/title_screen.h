#pragma once

#include "../../engine/core/scene.h"
#include "../../engine/core/game_loop.h"
#include <cstdint>

namespace game::scenes {

struct Texture {
    int width, height;  // actual image dimensions
    int texWidth, texHeight;  // power-of-2 dimensions for GPU
    uint32_t* data;
};

class TitleScreen : public engine::core::Scene {
public:
    explicit TitleScreen(engine::GameLoop& game);

    void onEnter() override;
    void onExit()  override;
    void update(float dt) override;
    void draw() override;

private:
    engine::GameLoop& m_game;

    Texture* m_background = nullptr;
    int  m_menuIndex;      // 0 = start, 1 = options, etc.
    bool m_startPressed;
};

} // namespace game::scenes
