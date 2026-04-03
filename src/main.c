#include "../common/callbacks.h"
#include "graphics/allocateVram.h"
#include "graphics/graphicsBoilerplate.h"
#include <pspuser.h>
#include <pspdebug.h>
#include <pspgu.h> 
#include <pspctrl.h> 
#include <pspdisplay.h>
#include <controller/userInput.h>
#include <stdlib.h> 
#include <stdio.h>

// PSP_MODULE_INFO is required
PSP_MODULE_INFO("Hello World", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

// Definition of PSP Width and Height
#define PSP_BUF_WIDTH (512) 
#define PSP_SCR_WIDTH (480)
#define PSP_SCR_HEIGHT (272)

// Global Variable that starts the game loop
int running = 1;
// GE List, this is basically where the sceGu commands are stored before being sent to the GE, rendering
static unsigned int __attribute__((aligned(16))) list [262144];

int main()
{ 
    SetupCallbacks();
    initGraphics(); // initialize the graphjics system, 
    sceCtrlSetSamplingCycle(0); // set the sampling cycle to 0, which means it will sample the controller as fast as possible, this is important for responsive controls 
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG); // set the sampling mode to analog, which means it will sample the analog stick as well as the buttons, this is important for games that use the analog stick for movement  

    while (running) {
        startFrame(); 
        
        // User Input definition
        pollLatch(); 
        pollPad(); 


        
        // Title Screen 

        if (gameState == STATE_TITLE_SCREEN) { 
            TitleAction action = titleScreenUpdate();
            if (titleScreenShutdown(action)) { 
                running = 0; 
            }
            startFrame();
            titleScreenRender();
            endFrame();
        }

        // // from this point on user input can be used 

        // // this sets to black because 00 is no red, 00 is no green, and 00 is no blue, and FF is full alpha, so the color is fully opaque black
        // sceGuClearColor(0xFF000000); // set clear color to black
        // sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT); // clear the color and depth buffer to the clear color
        endFrame(); 
    }

    termGraphics(); 

    // exit game, import from callbacks.c
    sceKernelExitGame();
    return EXIT_SUCCESS; 
}
