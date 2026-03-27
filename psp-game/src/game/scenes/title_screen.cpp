#include "title_screen.h"

namespace game::scenes {

TitleScreen::TitleScreen(engine::GameLoop& game)
    : m_game{game}
    , m_menuIndex{0}
    , m_startPressed{false}
{}

void TitleScreen::onEnter() {
}

void TitleScreen::onExit() {
    // TODO: stop music, unload title-specific assets
}

void TitleScreen::update(float dt) {
    auto& input = m_game.input();

    if (input.pressed(PSP_CTRL_UP))   m_menuIndex--;
    if (input.pressed(PSP_CTRL_DOWN)) m_menuIndex++;

    // clamp to valid range
    if (m_menuIndex < 0) m_menuIndex = 0;
    if (m_menuIndex > 1) m_menuIndex = 1;
    if (m_menuIndex > 2) m_menuIndex = 2;

    if (input.pressed(PSP_CTRL_CROSS)) {
        if (m_menuIndex == 0) {
            // TODO: changeScene to Overworld
        }
        if (m_menuIndex == 1) {
            // TODO: load saved game
        }
        if (m_menuIndex == 2) {
            // TODO: settings probably 
        }
 
    }
}

void TitleScreen::draw() {
    m_game.renderer().clear(RGB(0, 0, 0));

    // title — centered on 480px wide screen
    // OSLib default font is 8px wide per char, "LETDOWN" = 7 chars = 56px
    // center: (480 - 56) / 2 = 212
    oslDrawString(212, 60, "LETDOWN");

    // menu items — left aligned with small margin
    oslDrawString(40, 160, "New Game");
    oslDrawString(40, 180, "Load Game");

    // cursor
    int cursorY = 160 + (m_menuIndex * 20);
    oslDrawString(24, cursorY, ">");
}

} // namespace game::scenes
