#include "title_screen.h"

namespace game::scenes {

TitleScreen::TitleScreen(engine::GameLoop& game)
    : m_game{game}
    , m_menuIndex{0}
    , m_startPressed{false}
{}

void TitleScreen::onEnter() {
    // TODO: load title art & music via m_game.assets()
}

void TitleScreen::onExit() {
    // TODO: stop music, unload title-specific assets
}

void TitleScreen::update(float dt) {
    // TODO: navigate menu with d-pad, confirm with cross, push Overworld scene
}

void TitleScreen::draw() {
    // TODO: draw background, logo, menu items with highlight on m_menuIndex
}

} // namespace game::scenes
