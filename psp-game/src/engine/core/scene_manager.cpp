#include "scene_manager.h"

namespace engine::core {

// push a new scene onto the stack, calling onEnter() on it
void SceneManager::pushScene(std::unique_ptr<Scene> scene) {
    // guarding against a null scene being pushed, which would cause crash at runtime when dereferenced 
    if (!scene) {
        throw std::invalid_argument("SceneManager::pushScene: scene cannot be null");
    }
    scene->onEnter();
    m_scenes.push(std::move(scene));
}

// pop the top scene, calling onExit() on it
void SceneManager::popScene() {
    // changeScene() guarantees this won't be called on an empty stack, but just to be safe as this can cause crash at runtime
    if (m_scenes.empty()) {
        throw std::invalid_argument("SceneManager::popScene: scene stack is empty");
    }
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
