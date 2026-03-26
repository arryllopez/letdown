#pragma once

#include <oslib/oslib.h>
#include <string>

namespace engine::graphics {

/// A positioned image that can be drawn each frame.
class Sprite {
public:
    Sprite();
    ~Sprite();

    void load(const std::string& path);
    void draw(float x, float y);
    void setFrame(int frameX, int frameY, int w, int h);

    [[nodiscard]] int width()  const { return m_w; }
    [[nodiscard]] int height() const { return m_h; }

private:
    OSL_IMAGE* m_image;
    int m_w;
    int m_h;
};

} // namespace engine::graphics
