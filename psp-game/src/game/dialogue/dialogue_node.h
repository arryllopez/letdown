#pragma once

#include <string>
#include <vector>

namespace game::dialogue {

/// One beat of dialogue — speaker, text, and optional branching choices.
struct DialogueChoice {
    std::string text;
    int nextNodeId;
};

struct DialogueNode {
    int         id;
    std::string speaker;
    std::string text;
    std::vector<DialogueChoice> choices;  // empty = linear, just go to next
    int nextNodeId;                       // used when choices is empty
};

} // namespace game::dialogue
