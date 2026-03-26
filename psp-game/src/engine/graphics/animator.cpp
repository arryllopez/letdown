#include "animator.h"

namespace engine::graphics {

Animator::Animator()
    : m_frameIndex{0}
    , m_elapsed{0.0f}
{}

void Animator::addAnimation(const std::string& name,
                            const std::vector<AnimFrame>& frames,
                            float fps)
{
    // TODO: store animation data in m_anims map
}

void Animator::play(const std::string& name, bool loop) {
    // TODO: set m_current, reset frame index & elapsed if different animation
}

void Animator::update(float dt) {
    // TODO: accumulate dt, advance m_frameIndex when enough time passes, handle loop/clamp
}

void Animator::apply(Sprite& sprite) const {
    // TODO: grab current AnimFrame, call sprite.setFrame()
}

} // namespace engine::graphics
