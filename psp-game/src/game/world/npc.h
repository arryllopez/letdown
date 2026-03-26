#pragma once

#include "../../engine/graphics/sprite.h"
#include "../../engine/graphics/animator.h"
#include <string>

namespace game::world {

/// A non-player character on the overworld.
/// Has a position, a sprite, and a dialogue script to trigger on interact.
struct NPC {
    float x, y;
    std::string name;
    std::string dialoguePath;   // path to dialogue script file

    engine::graphics::Sprite   sprite;
    engine::graphics::Animator animator;

    // TODO: interaction radius, facing direction, patrol path, etc.
};

} // namespace game::world
