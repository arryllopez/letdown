#include "title_screen.h"

#include "../../controller/userInput.h"

#include <pspctrl.h>

typedef enum {
    MENU_START_GAME = 0,
    MENU_LOAD_GAME,
    MENU_EXIT,
    MENU_COUNT
} TitleMenuItem;

static int selectedIndex;

static void titleScreenBackgroundRender(void) {
}

static void titleScreenRenderMenu(void) {
}

void titleScreenInit(void) {
    selectedIndex = MENU_START_GAME;
}

TitleAction titleScreenUpdate(void) {
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
