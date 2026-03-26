#pragma once

#include "dialogue_node.h"
#include <vector>
#include <string>

namespace game::dialogue {

/// Reads a dialogue script file and returns a list of nodes.
/// File format is yours to define — JSON, custom DSL, whatever fits in 32 MB.
class DialogueParser {
public:
    // TODO: parse file at path, return ordered node list
    static std::vector<DialogueNode> parse(const std::string& path);
};

} // namespace game::dialogue
