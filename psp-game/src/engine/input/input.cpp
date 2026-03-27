#include "input.h"

namespace engine::input {

Input::Input()
    : m_current{}
    , m_previous{}
{
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
}

void Input::update() {
    m_previous = m_current;
    sceCtrlReadBufferPositive(&m_current, 1);
}

bool Input::held(uint32_t btn) const {
    return (m_current.Buttons & btn) != 0;
}

bool Input::pressed(uint32_t btn) const {
    return (m_current.Buttons & btn) != 0
        && (m_previous.Buttons & btn) == 0;
}

bool Input::released(uint32_t btn) const {
    return (m_current.Buttons & btn) == 0
        && (m_previous.Buttons & btn) != 0;
}

float Input::analogX() const {
    return (static_cast<float>(m_current.Lx) - 128.0f) / 128.0f;
}

float Input::analogY() const {
    return (static_cast<float>(m_current.Ly) - 128.0f) / 128.0f;
}

} // namespace engine::input
