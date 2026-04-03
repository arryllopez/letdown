#pragma once

typedef enum {
    TITLE_ACTION_NONE = 0,
    TITLE_ACTION_START_GAME,
    TITLE_ACTION_QUIT
} TitleAction;
void titleScreenInit(void);
TitleAction titleScreenUpdate(void);  // input + menu + animation tick
void titleScreenRender(void);         // draw bg/logo/menu
void titleScreenShutdown(void);