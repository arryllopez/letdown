#pragma once

#include "scene.h"
#include <memory>
#include <stack>
#include <stdexcept>

namespace engine::core {

/// Push/pop scene stack. Top scene gets update() and draw().
class SceneManager {
public:
    void pushScene(std::unique_ptr<Scene> scene);
    void popScene();
    void changeScene(std::unique_ptr<Scene> scene);

    void update(float dt);
    void draw();

    [[nodiscard]] bool empty() const { return m_scenes.empty(); }

private:
    std::stack<std::unique_ptr<Scene>> m_scenes;
};

} // namespace engine::core
