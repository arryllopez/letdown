#pragma once

#include <oslib/oslib.h>

namespace engine::graphics {

/// Wraps OSLib draw calls.
/// Owns the frame begin/end and any global draw state (camera offset, etc.).
class Renderer {
public:
    Renderer();
    ~Renderer();

    void beginFrame();
    void endFrame();
    void clear(unsigned int color = 0);

    void setCameraOffset(float x, float y);
    [[nodiscard]] float cameraX() const { return m_camX; }
    [[nodiscard]] float cameraY() const { return m_camY; }

private:
    float m_camX;
    float m_camY;
};

} // namespace engine::graphics
