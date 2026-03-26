#include "renderer.h"

namespace engine::graphics {

Renderer::Renderer()
    : m_camX{0.0f}
    , m_camY{0.0f}
{
    // TODO: any one-time GPU state setup
}

Renderer::~Renderer() = default;

void Renderer::beginFrame() {
    // TODO: oslStartDrawing(), clear buffer
}

void Renderer::endFrame() {
    // TODO: oslEndDrawing(), oslSyncFrame()
}

void Renderer::clear(unsigned int color) {
    // TODO: oslClearScreen(color)
}

void Renderer::setCameraOffset(float x, float y) {
    // TODO: store offset, will be applied when drawing sprites/tiles
    m_camX = x;
    m_camY = y;
}

} // namespace engine::graphics
