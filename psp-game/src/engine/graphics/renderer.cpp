#include "renderer.h"

namespace engine::graphics {

Renderer::Renderer()
    : m_camX{0.0f}
    , m_camY{0.0f}
{
    // TODO: any one-time GPU state setup
}

Renderer::~Renderer() = default;

// Drawing a new frame
void Renderer::beginFrame() {
    oslStartDrawing();
}


// End the draw frame and sync to vsync
void Renderer::endFrame() {
    oslEndDrawing();
    oslSyncFrame();
}

void Renderer::clear(unsigned int color) {
  oslClearScreen(color);   
}

void Renderer::setCameraOffset(float x, float y) {
    // TODO: store offset, will be applied when drawing sprites/tiles
    m_camX = x;
    m_camY = y;
}

} // namespace engine::graphics
