#pragma once

#include "../../engine/graphics/sprite.h"
#include "../../engine/graphics/animator.h"
#include "../../engine/input/input.h"

namespace game::world {

class TileMap;

class Player {
public:
    Player();

    void update(float dt, const engine::input::Input& input, const TileMap& map);
    void draw(engine::graphics::Renderer& renderer);

    float x() const { return m_x; }
    float y() const { return m_y; }

private:
    float m_x, m_y;
    float m_speed;

    engine::graphics::Sprite   m_sprite;
    engine::graphics::Animator m_animator;
};

} // namespace game::world
