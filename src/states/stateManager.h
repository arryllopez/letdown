#pragma once

typedef enum {
    GAME_STATE_TITLE = 0,
    GAME_STATE_SCENE1,
    GAME_STATE_SCENE2,
    GAME_STATE_SCENE3,
    GAME_STATE_SCENE4
} GameState;

void stateManagerInit(void);
void stateManagerUpdate(void);
void stateManagerRender(void);
int stateManagerWantsQuit(void);
GameState stateManagerGetState(void);
