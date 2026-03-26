#pragma once

#include <pspctrl.h>
#include <cstdint>

namespace engine::input {

/// Thin wrapper around pspctrl.
/// Tracks current + previous frame so you can query pressed / held / released.
class Input {
public:
    Input();

    void update();

    [[nodiscard]] bool held(uint32_t btn)     const;
    [[nodiscard]] bool pressed(uint32_t btn)  const;
    [[nodiscard]] bool released(uint32_t btn) const;

    [[nodiscard]] float analogX() const;   // -1.0 .. 1.0
    [[nodiscard]] float analogY() const;

private:
    SceCtrlData m_current;
    SceCtrlData m_previous;
};

} // namespace engine::input
