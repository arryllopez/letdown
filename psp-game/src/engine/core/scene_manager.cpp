#include "scene_manager.h"

namespace engine::core {

// push a new scene onto the stack, calling onEnter() on it
void SceneManager::pushScene(std::unique_ptr<Scene> scene) {
    scene->onEnter();
    m_scenes.push(std::move(scene));
}

// pop the top scene, calling onExit() on it
void SceneManager::popScene() {
    m_scenes.top()->onExit();
    m_scenes.pop();

}

// handle the transition between scenes
void SceneManager::changeScene(std::unique_ptr<Scene> scene) {
    // if the stack is not empty pop the current scene first
    if (!m_scenes.empty()) {
        popScene();
    }
    // then push the new scene
    pushScene(std::move(scene));
}

void SceneManager::update(float dt) {
    if (!m_scenes.empty()) {
        m_scenes.top()->update(dt);
    }
}

void SceneManager::draw() {
    if (!m_scenes.empty()) {
        m_scenes.top()->draw();
    }
}

} 
