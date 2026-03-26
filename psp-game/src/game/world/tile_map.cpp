#include "tile_map.h"

namespace game::world {

TileMap::TileMap()
    : m_width{0}
    , m_height{0}
    , m_tileSize{16}
{}

void TileMap::load(const std::string& path) {
    // TODO: open file, read width/height/tileSize, fill m_tiles and m_collision
}

void TileMap::draw(engine::graphics::Renderer& renderer) {
    // TODO: iterate visible tiles (camera culled), draw each with tileset sub-rect
}

bool TileMap::isSolid(int tileX, int tileY) const {
    // TODO: bounds check, return m_collision[tileY * m_width + tileX]
    return false;
}

} // namespace game::world
