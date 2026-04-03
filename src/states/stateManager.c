#include "stateManager.h"

#include "title/title_screen.h"

#include "../controller/userInput.h"

#include <pspctrl.h>

static GameState currentState = GAME_STATE_TITLE;
static int wantsQuit;

static void updateTitle(void) {
    TitleAction action = titleScreenUpdate();

    if (titleScreenShutdown(action)) {
        wantsQuit = 1;
        return;
    }

    if (action == TITLE_ACTION_START_GAME || action == TITLE_ACTION_LOAD_GAME) {
        currentState = GAME_STATE_SCENE1;
    }
}

static void updateScene(void) {
    if (isKeyDown(PSP_CTRL_START)) {
        wantsQuit = 1;
        return;
    }

    if (isKeyDown(PSP_CTRL_RTRIGGER) && currentState < GAME_STATE_SCENE4) {
        currentState = (GameState)(currentState + 1);
    }

    if (isKeyDown(PSP_CTRL_LTRIGGER) && currentState > GAME_STATE_SCENE1) {
        currentState = (GameState)(currentState - 1);
    }

    if (isKeyDown(PSP_CTRL_TRIANGLE)) {
        currentState = GAME_STATE_TITLE;
        titleScreenInit();
    }
}

void stateManagerInit(void) {
    currentState = GAME_STATE_TITLE;
    wantsQuit = 0;
    titleScreenInit();
}

void stateManagerUpdate(void) {
    switch (currentState) {
        case GAME_STATE_TITLE:
            updateTitle();
            break;
        case GAME_STATE_SCENE1:
        case GAME_STATE_SCENE2:
        case GAME_STATE_SCENE3:
        case GAME_STATE_SCENE4:
            updateScene();
            break;
    }
}

void stateManagerRender(void) {
    switch (currentState) {
        case GAME_STATE_TITLE:
            titleScreenRender();
            break;
        case GAME_STATE_SCENE1:
        case GAME_STATE_SCENE2:
        case GAME_STATE_SCENE3:
        case GAME_STATE_SCENE4:
            break;
    }
}

int stateManagerWantsQuit(void) {
    return wantsQuit;
}

GameState stateManagerGetState(void) {
    return currentState;
}
