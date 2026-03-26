#include "overworld.h"

namespace game::scenes {

Overworld::Overworld(engine::GameLoop& game)
    : m_game{game}
    , m_inDialogue{false}
{}

void Overworld::onEnter() {
    // TODO: load map, spawn player at entry point, load NPCs
}

void Overworld::onExit() {
    // TODO: unload map assets
}

void Overworld::update(float dt) {
    if (m_inDialogue) {
        // TODO: update dialogue renderer, check for completion
        return;
    }

    // TODO: update player, check NPC interaction trigger, update camera
}

void Overworld::draw() {
    // TODO: draw map, NPCs, player (painter's order)
    // TODO: if m_inDialogue, draw dialogue box on top
}

} // namespace game::scenes
