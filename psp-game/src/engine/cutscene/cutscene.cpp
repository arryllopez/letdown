#include "cutscene.h"

namespace engine::cutscene {

Cutscene::Cutscene()
    : m_index{0}
    , m_timer{0.0f}
    , m_finished{true}
{}

void Cutscene::load(const std::vector<CutsceneStep>& steps) {
    // TODO: store steps, reset state
}

void Cutscene::start() {
    // TODO: set m_index = 0, m_finished = false, m_timer = 0
}

void Cutscene::update(float dt) {
    // TODO: tick timer, auto-advance timed steps, handle fade/camera
}

void Cutscene::advance() {
    // TODO: if current step is indefinite, move to next step
}

const CutsceneStep* Cutscene::currentStep() const {
    // TODO: return &m_steps[m_index] if valid, else nullptr
    return nullptr;
}

} // namespace engine::cutscene
