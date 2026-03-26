#pragma once

#include "sprite.h"
#include <vector>
#include <string>

namespace engine::graphics {

/// Drives sprite-sheet animation: frame list, timing, looping.
struct AnimFrame {
    int x, y, w, h;  // sub-rect in the sheet
};

class Animator {
public:
    Animator();

    void addAnimation(const std::string& name, const std::vector<AnimFrame>& frames, float fps);
    void play(const std::string& name, bool loop = true);
    void update(float dt);
    void apply(Sprite& sprite) const;

    [[nodiscard]] const std::string& currentAnimation() const { return m_current; }

private:
    struct Animation {
        std::vector<AnimFrame> frames;
        float fps;
        bool  loop;
    };

    std::unordered_map<std::string, Animation> m_anims;
    std::string m_current;
    int         m_frameIndex;
    float       m_elapsed;
};

} // namespace engine::graphics
