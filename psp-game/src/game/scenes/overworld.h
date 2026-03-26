#pragma once

#include "../../engine/core/scene.h"
#include "../../engine/core/game_loop.h"
#include "../world/tile_map.h"
#include "../world/player.h"
#include "../world/npc.h"
#include "../dialogue/dialogue_renderer.h"
#include <vector>

namespace game::scenes {

class Overworld : public engine::core::Scene {
public:
    explicit Overworld(engine::GameLoop& game);

    void onEnter() override;
    void onExit()  override;
    void update(float dt) override;
    void draw() override;

private:
    engine::GameLoop& m_game;

    world::TileMap  m_map;
    world::Player   m_player;
    std::vector<world::NPC> m_npcs;

    dialogue::DialogueRenderer m_dialogueRenderer;
    bool m_inDialogue;
};

} // namespace game::scenes
