#include "sprite.h"

namespace engine::graphics {

Sprite::Sprite()
    : m_image{nullptr}
    , m_w{0}
    , m_h{0}
{}

Sprite::~Sprite() {
    // TODO: oslDeleteImage if owned
}

void Sprite::load(const std::string& path) {
    // TODO: load PNG via oslLoadImageFilePNG, store dimensions
}

void Sprite::draw(float x, float y) {
    // TODO: set position on m_image, oslDrawImage
}

void Sprite::setFrame(int frameX, int frameY, int w, int h) {
    // TODO: oslSetImageTileSize for sprite-sheet sub-rect
}

} // namespace engine::graphics
