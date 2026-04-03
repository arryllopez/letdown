#pragma once

typedef enum {
    TITLE_ACTION_NONE = 0,
    TITLE_ACTION_START_GAME,
    TITLE_ACTION_LOAD_GAME,
    TITLE_ACTION_SETTINGS,
    TITLE_ACTION_QUIT
} TitleAction;

void titleScreenInit(void);
TitleAction titleScreenUpdate(void);
void titleScreenRender(void);
int titleScreenShutdown(TitleAction action);
