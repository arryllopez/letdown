#pragma once

#include "../../engine/core/scene.h"
#include "../../engine/core/game_loop.h"

namespace game::scenes {

class TitleScreen : public engine::core::Scene {
public:
    explicit TitleScreen(engine::GameLoop& game);

    void onEnter() override;
    void onExit()  override;
    void update(float dt) override;
    void draw() override;

private:
    engine::GameLoop& m_game;

    int  m_menuIndex;      // 0 = start, 1 = options, etc.
    bool m_startPressed;
    // TODO: background image, logo sprite, menu items
};

} // namespace game::scenes
