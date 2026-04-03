#include "../common/callbacks.h"
#include "graphics/graphicsBoilerplate.h"
#include "states/stateManager.h"
#include <pspuser.h>
#include <controller/userInput.h>
#include <pspctrl.h>
#include <pspgu.h>
#include <stdlib.h>

// PSP_MODULE_INFO is required
PSP_MODULE_INFO("Hello World", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

// Global Variable that starts the game loop
int running = 1;

int main()
{ 
    SetupCallbacks();
    initGraphics();
    stateManagerInit();
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    while (running) {
        pollLatch();
        pollPad();

        stateManagerUpdate();
        if (stateManagerWantsQuit()) {
            running = 0;
            break;
        }

        startFrame();
        sceGuClearColor(0xFF000000);
        sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
        stateManagerRender();
        endFrame();
    }

    termGraphics(); 

    // exit game, import from callbacks.c
    sceKernelExitGame();
    return EXIT_SUCCESS; 
}
