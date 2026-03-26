#pragma once

#include <vector>
#include <string>
#include <functional>

namespace engine::cutscene {

/// A step in a cutscene — could be dialogue, camera pan, wait, fade, etc.
struct CutsceneStep {
    enum class Type { Dialogue, Wait, FadeIn, FadeOut, CameraMove };
    Type type;
    float duration;          // seconds (0 = indefinite / advance on input)
    std::string data;        // meaning depends on type
};

/// Plays a linear sequence of CutsceneSteps.
class Cutscene {
public:
    Cutscene();

    void load(const std::vector<CutsceneStep>& steps);
    void start();
    void update(float dt);
    void advance();          // player pressed confirm

    [[nodiscard]] bool isFinished() const { return m_finished; }
    [[nodiscard]] const CutsceneStep* currentStep() const;

private:
    std::vector<CutsceneStep> m_steps;
    std::size_t m_index;
    float       m_timer;
    bool        m_finished;
};

} // namespace engine::cutscene
