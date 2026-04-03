#include "title_screen.h"

#include "../../controller/userInput.h"
#include "../../graphics/allocateVram.h"

#include <pspgu.h>
#include <pspctrl.h>

typedef enum {
    MENU_START_GAME = 0,
    MENU_LOAD_GAME,
    MENU_SETTINGS,
    MENU_EXIT,
    MENU_COUNT
} TitleMenuItem;

static int selectedIndex;
static int tickCount;

enum {
    SCREEN_WIDTH = 480,
    SCREEN_HEIGHT = 272,
    BG_FRAME_WIDTH = 240,
    BG_FRAME_HEIGHT = 136,
    BG_FRAME_COUNT = 4,
    BG_TEX_WIDTH = 256,
    BG_TEX_HEIGHT = 1024,
    BG_FRAME_TICKS = 10
};

typedef struct {
    float u;
    float v;
    unsigned int color;
    float x;
    float y;
    float z;
} Vertex;

static unsigned int* backgroundSheet;

static unsigned int makeColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    return (a << 24) | (b << 16) | (g << 8) | r;
}

static void putSheetPixel(int x, int y, unsigned int color) {
    backgroundSheet[y * BG_TEX_WIDTH + x] = color;
}

static void buildBackgroundSheet(void) {
    int frame;
    int y;
    int x;

    if (backgroundSheet != NULL) {
        return;
    }

    backgroundSheet = (unsigned int*)getVramTexture(BG_TEX_WIDTH, BG_TEX_HEIGHT, GU_PSM_8888);

    for (y = 0; y < BG_TEX_HEIGHT; ++y) {
        for (x = 0; x < BG_TEX_WIDTH; ++x) {
            putSheetPixel(x, y, makeColor(5, 6, 14, 255));
        }
    }

    for (frame = 0; frame < BG_FRAME_COUNT; ++frame) {
        int yOffset = frame * BG_FRAME_HEIGHT;

        for (y = 0; y < BG_FRAME_HEIGHT; ++y) {
            for (x = 0; x < BG_FRAME_WIDTH; ++x) {
                unsigned int r = 10 + (unsigned int)(x / 16);
                unsigned int g = 20 + (unsigned int)((y + frame * 18) / 7);
                unsigned int b = 40 + (unsigned int)((x + y + frame * 24) / 6);
                unsigned int wave = (unsigned int)((x + frame * 26 + y / 4) % 64);
                unsigned int color = makeColor(r + wave / 5, g + wave / 4, b + wave / 3, 255);
                putSheetPixel(x, yOffset + y, color);
            }
        }

        for (x = 0; x < BG_FRAME_WIDTH; ++x) {
            int lineY = ((x * 2) + frame * 13) % BG_FRAME_HEIGHT;
            putSheetPixel(x, yOffset + lineY, makeColor(118, 173, 255, 255));
        }

        for (x = 0; x < 24; ++x) {
            int starX = (x * 17 + frame * 31) % BG_FRAME_WIDTH;
            int starY = (x * 11 + frame * 7) % BG_FRAME_HEIGHT;
            putSheetPixel(starX, yOffset + starY, makeColor(220, 233, 255, 255));
        }
    }
}

static void drawRect(float x, float y, float w, float h, unsigned int color) {
    Vertex* verts;

    sceGuDisable(GU_TEXTURE_2D);

    verts = (Vertex*)sceGuGetMemory(2 * sizeof(Vertex));
    verts[0].color = color;
    verts[0].x = x;
    verts[0].y = y;
    verts[0].z = 0.0f;
    verts[1].color = color;
    verts[1].x = x + w;
    verts[1].y = y + h;
    verts[1].z = 0.0f;

    sceGuDrawArray(
        GU_SPRITES,
        GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D,
        2,
        0,
        verts
    );
}

static void drawAnimatedBackground(void) {
    int frame = (tickCount / BG_FRAME_TICKS) % BG_FRAME_COUNT;
    float v0 = (float)(frame * BG_FRAME_HEIGHT);
    float v1 = (float)((frame + 1) * BG_FRAME_HEIGHT);
    Vertex* verts;

    buildBackgroundSheet();

    sceGuEnable(GU_TEXTURE_2D);
    sceGuTexMode(GU_PSM_8888, 0, 0, 0);
    sceGuTexImage(0, BG_TEX_WIDTH, BG_TEX_HEIGHT, BG_TEX_WIDTH, backgroundSheet);
    sceGuTexFilter(GU_LINEAR, GU_LINEAR);
    sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);

    verts = (Vertex*)sceGuGetMemory(2 * sizeof(Vertex));
    verts[0].u = 0.0f;
    verts[0].v = v0;
    verts[0].color = 0xffffffff;
    verts[0].x = 0.0f;
    verts[0].y = 0.0f;
    verts[0].z = 0.0f;

    verts[1].u = (float)BG_FRAME_WIDTH;
    verts[1].v = v1;
    verts[1].color = 0xffffffff;
    verts[1].x = (float)SCREEN_WIDTH;
    verts[1].y = (float)SCREEN_HEIGHT;
    verts[1].z = 0.0f;

    sceGuDrawArray(
        GU_SPRITES,
        GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D,
        2,
        0,
        verts
    );
}

// Render the background of the title screen
static void titleScreenBackgroundRender(void) {
    drawAnimatedBackground();
}

// Render the menu options of the title screen
static void titleScreenRenderMenu(void) {
    int i;
    const float menuX = 132.0f;
    const float menuY = 118.0f;
    const float itemW = 216.0f;
    const float itemH = 28.0f;
    const float gap = 10.0f;

    drawRect(108.0f, 94.0f, 264.0f, 166.0f, makeColor(12, 15, 30, 180));

    for (i = 0; i < MENU_COUNT; ++i) {
        float y = menuY + i * (itemH + gap);
        unsigned int base = makeColor(48, 63, 97, 220);
        unsigned int accent = makeColor(123, 185, 248, 255);

        if (i == selectedIndex) {
            drawRect(menuX - 22.0f, y + 8.0f, 10.0f, 10.0f, accent);
            drawRect(menuX, y, itemW, itemH, makeColor(74, 118, 191, 245));
            drawRect(menuX + 4.0f, y + 4.0f, itemW - 8.0f, itemH - 8.0f, makeColor(18, 28, 52, 245));
            drawRect(menuX + 10.0f, y + 11.0f, itemW - 20.0f, 6.0f, accent);
        } else {
            drawRect(menuX, y, itemW, itemH, base);
            drawRect(menuX + 5.0f, y + 5.0f, itemW - 10.0f, itemH - 10.0f, makeColor(14, 20, 37, 220));
        }
    }
}

void titleScreenInit(void) {
    selectedIndex = MENU_START_GAME;
    tickCount = 0;
}

TitleAction titleScreenUpdate(void) {
    ++tickCount;

    if (isKeyDown(PSP_CTRL_UP)) {
        selectedIndex = (selectedIndex + MENU_COUNT - 1) % MENU_COUNT;
    }

    if (isKeyDown(PSP_CTRL_DOWN)) {
        selectedIndex = (selectedIndex + 1) % MENU_COUNT;
    }

    if (isKeyDown(PSP_CTRL_CROSS)) {
        if (selectedIndex == MENU_START_GAME) {
            return TITLE_ACTION_START_GAME;
        }
        if (selectedIndex == MENU_LOAD_GAME) {
            return TITLE_ACTION_LOAD_GAME;
        }
        if (selectedIndex == MENU_SETTINGS) {
            return TITLE_ACTION_SETTINGS;
        }
        if (selectedIndex == MENU_EXIT) {
            return TITLE_ACTION_QUIT;
        }
    }

    return TITLE_ACTION_NONE;
}

void titleScreenRender(void) {
    titleScreenBackgroundRender();
    titleScreenRenderMenu();
}

int titleScreenShutdown(TitleAction action) {
    if (action == TITLE_ACTION_QUIT) {
        return 1;
    }

    if (isKeyDown(PSP_CTRL_START)) {
        return 1;
    }

    return 0;
}
