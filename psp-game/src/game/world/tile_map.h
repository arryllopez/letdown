#pragma once

#include "../../engine/graphics/renderer.h"
#include <vector>
#include <string>
#include <cstdint>

namespace game::world {

/// Simple 2D tile map — grid of tile IDs, rendered with a tileset image.
class TileMap {
public:
    TileMap();

    void load(const std::string& path);   // TODO: define your map format
    void draw(engine::graphics::Renderer& renderer);

    [[nodiscard]] int  width()  const { return m_width; }
    [[nodiscard]] int  height() const { return m_height; }
    [[nodiscard]] int  tileSize() const { return m_tileSize; }
    [[nodiscard]] bool isSolid(int tileX, int tileY) const;

private:
    int m_width;       // in tiles
    int m_height;
    int m_tileSize;    // pixels per tile
    std::vector<uint16_t> m_tiles;      // row-major tile IDs
    std::vector<bool>     m_collision;  // per-tile solidity
    // TODO: tileset OSL_IMAGE*
};

} // namespace game::world
