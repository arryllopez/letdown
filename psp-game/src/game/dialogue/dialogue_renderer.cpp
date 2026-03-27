#include "dialogue_renderer.h"

namespace game::dialogue {

DialogueRenderer::DialogueRenderer()
    : m_node{nullptr}
    , m_charTimer{0.0f}
    , m_visibleChars{0}
    , m_choiceIndex{0}
    , m_complete{true}
{}

void DialogueRenderer::show(const DialogueNode& node) {
    // TODO: set m_node, reset typewriter state
}

void DialogueRenderer::update(float dt, const engine::input::Input& input) {
    // TODO: advance typewriter timer, handle choice selection with d-pad
}

void DialogueRenderer::draw(engine::graphics::Renderer& renderer) {
    // TODO: draw dialogue box, speaker name, visible text, choice highlights
}

} // namespace game::dialogue
