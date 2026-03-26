#include "input.h"

namespace engine::input {

Input::Input()
    : m_current{}
    , m_previous{}
{
    // TODO: sceCtrlSetSamplingCycle / sceCtrlSetSamplingMode
}

void Input::update() {
    // TODO: copy current -> previous, sceCtrlReadBufferPositive into current
}

bool Input::held(uint32_t btn) const {
    // TODO: return (m_current.Buttons & btn) != 0
    return false;
}

bool Input::pressed(uint32_t btn) const {
    // TODO: held this frame, not held last frame
    return false;
}

bool Input::released(uint32_t btn) const {
    // TODO: not held this frame, held last frame
    return false;
}

float Input::analogX() const {
    // TODO: normalize m_current.Lx from [0,255] to [-1,1]
    return 0.0f;
}

float Input::analogY() const {
    // TODO: normalize m_current.Ly from [0,255] to [-1,1]
    return 0.0f;
}

} // namespace engine::input
