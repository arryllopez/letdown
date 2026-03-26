#include "player.h"
#include "tile_map.h"

namespace game::world {

Player::Player()
    : m_x{0.0f}
    , m_y{0.0f}
    , m_speed{60.0f}   // pixels per second
{}

void Player::update(float dt, const engine::input::Input& input, const TileMap& map) {
    // TODO: read d-pad / analog, compute velocity, check collision with map, move
    // TODO: update animator
}

void Player::draw(engine::graphics::Renderer& renderer) {
    // TODO: apply animator to sprite, draw at (m_x, m_y) offset by camera
}

} // namespace game::world
