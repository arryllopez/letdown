#include "title_screen.h"
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <cstdlib>
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

typedef struct {
    float u, v;
    uint32_t colour;
    float x, y, z;
} TextureVertex;

using game::scenes::Texture;

// Round up to next power of 2
static int nextPow2(int v) {
    v--;
    v |= v >> 1; v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16;
    return v + 1;
}

static Texture* loadTexture(const char* filename) {
    int w, h;
    uint32_t* pixels = (uint32_t*)stbi_load(filename, &w, &h, nullptr, STBI_rgb_alpha);
    if (!pixels) return nullptr;

    int tw = nextPow2(w);  // 480 -> 512
    int th = nextPow2(h);  // 272 -> 512

    // Allocate power-of-2 buffer and copy rows into it
    uint32_t* padded = (uint32_t*)calloc(tw * th, sizeof(uint32_t));
    for (int y = 0; y < h; y++) {
        memcpy(padded + y * tw, pixels + y * w, w * sizeof(uint32_t));
    }
    stbi_image_free(pixels);

    Texture* texture = (Texture*)calloc(1, sizeof(Texture));
    texture->width = w;
    texture->height = h;
    texture->texWidth = tw;
    texture->texHeight = th;
    texture->data = padded;

    sceKernelDcacheWritebackInvalidateAll();
    return texture;
}

static void drawTexture(Texture* texture, float x, float y, float w, float h) {
    static TextureVertex vertices[2];

    vertices[0].u = 0.0f;
    vertices[0].v = 0.0f;
    vertices[0].colour = 0xFFFFFFFF;
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].z = 0.0f;

    vertices[1].u = w;
    vertices[1].v = h;
    vertices[1].colour = 0xFFFFFFFF;
    vertices[1].x = x + w;
    vertices[1].y = y + h;
    vertices[1].z = 0.0f;

    sceGuTexMode(GU_PSM_8888, 0, 0, GU_FALSE);
    sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
    sceGuTexImage(0, texture->texWidth, texture->texHeight, texture->texWidth, texture->data);

    sceGuEnable(GU_TEXTURE_2D);
    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
    sceGuDisable(GU_TEXTURE_2D);
}

namespace game::scenes {

TitleScreen::TitleScreen(engine::GameLoop& game)
    : m_game{game}
    , m_background{nullptr}
    , m_menuIndex{0}
    , m_startPressed{false}
{}

void TitleScreen::onEnter() {
    m_background = loadTexture("ms0:/PSP/GAME/letdown/assets/sprites/title_screenbg.png");
}

void TitleScreen::onExit() {
    if (m_background) {
        if (m_background->data) free(m_background->data);
        free(m_background);
        m_background = nullptr;
    }
}

void TitleScreen::update(float dt) {
    auto& input = m_game.input();

    if (input.pressed(PSP_CTRL_UP))   m_menuIndex--;
    if (input.pressed(PSP_CTRL_DOWN)) m_menuIndex++;

    // clamp to valid range
    if (m_menuIndex < 0) m_menuIndex = 0;
    if (m_menuIndex > 2) m_menuIndex = 2;

    if (input.pressed(PSP_CTRL_CROSS)) {
        if (m_menuIndex == 0) {
            // TODO: changeScene to Overworld
        }
        if (m_menuIndex == 1) {
            // TODO: load saved game
        }
        if (m_menuIndex == 2) {
            // TODO: settings probably
        }

    }
}

void TitleScreen::draw() {
    m_game.renderer().clear(RGB(0, 0, 0));

    // draw background image
    if (m_background) {
        drawTexture(m_background, 0, 0, m_background->width, m_background->height);
        // Reset GU state so OSLib text rendering works
        sceGuDisable(GU_TEXTURE_2D);
        sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    } else {
        oslDrawString(10, 10, "IMG FAILED TO LOAD");
    }

    oslSetTextColor(RGBA(100, 149, 237, 255));  // cornflower blue
    oslDrawString(212,60, "LETDOWN");

    // menu items — left aligned with small margin
    oslDrawString(40, 160, "New Game");
    oslDrawString(40, 180, "Load Game");
    oslDrawString(40, 200, "Settings");

    // cursor
    int cursorY = 160 + (m_menuIndex * 20);
    oslDrawString(24, cursorY, ">");
}

} // namespace game::scenes
