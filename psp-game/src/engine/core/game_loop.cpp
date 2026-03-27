#include "game_loop.h"
#include "../../game/scenes/title_screen.h"
#include <pspkernel.h>
#include <psprtc.h>

namespace engine {

GameLoop::GameLoop()
    : m_running{false}
{}

void GameLoop::run() {
    m_running = true;

    m_scenes.changeScene(std::make_unique<game::scenes::TitleScreen>(*this));
    

    u64 lastTick;
    sceRtcGetCurrentTick(&lastTick);
    const u32 tickRes = sceRtcGetTickResolution();

    while (m_running) {
        // Delta time
        u64 now;
        sceRtcGetCurrentTick(&now);
        float dt = static_cast<float>(now - lastTick) / static_cast<float>(tickRes);
        lastTick = now;

        // TODO: cap dt to avoid spiral of death (e.g. max 1/15s)

        m_input.update();

        if (!m_scenes.empty()) {
            m_scenes.update(dt);
        }

        m_renderer.beginFrame();
        if (!m_scenes.empty()) {
            m_scenes.draw();
        }
        m_renderer.endFrame();

        // TODO: check for exit condition and set m_running = false
    }
}

} // namespace engine
