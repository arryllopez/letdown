#include "title_screen.h" 
#include "../../controller/userInput.h" 
#include <pspctrl.h> 

typedef enum {
    TITLE_ACTION_NONE = 0,
    TITLE_ACTION_NEW_GAME,
    TITLE_ACTION_LOAD_GAME, 
    TITLE_ACTION_EXIT
} TitleAction;

void titleScreenInit() { 

}

TitleAction titleScreenUpdate() { 
    if (isKeyDown(PSP_CTRL_CROSS)) { 
        if (selectedIndex == MENU_START_GAME) { 
            return TITLE_ACTION_NEW_GAME; 
        } else if (selectedIndex == MENU_EXIT) { 
            return TITLE_ACTION_EXIT; 
        } else if (selectedIndex == MENU_LOAD_GAME) { 
            return TITLE_ACTION_LOAD_GAME; 
        }
    }
}

void titleScreenRender() { 

}

int titleScreenShutdown(void) {
    
}

