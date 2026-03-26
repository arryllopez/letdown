#pragma once

namespace engine::core {

/// Base class for every game screen (title, overworld, battle, etc.).
class Scene {
public:
    virtual ~Scene() = default;

    virtual void onEnter()  {}
    virtual void onExit()   {}
    virtual void update(float dt) = 0;
    virtual void draw()           = 0;
};

} // namespace engine::core
