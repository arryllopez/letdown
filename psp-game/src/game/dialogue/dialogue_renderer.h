#pragma once

#include "dialogue_node.h"

namespace engine::graphics { class Renderer; }
namespace engine::input   { class Input; }

namespace game::dialogue {

/// Draws the dialogue box, typewriter text, speaker name, choice highlights.
class DialogueRenderer {
public:
    DialogueRenderer();

    void show(const DialogueNode& node);
    void update(float dt, const engine::input::Input& input);
    void draw(engine::graphics::Renderer& renderer);

    [[nodiscard]] bool isComplete() const { return m_complete; }
    [[nodiscard]] int  selectedChoice() const { return m_choiceIndex; }

private:
    const DialogueNode* m_node;
    float  m_charTimer;      // typewriter effect accumulator
    int    m_visibleChars;
    int    m_choiceIndex;
    bool   m_complete;
};

} // namespace game::dialogue
