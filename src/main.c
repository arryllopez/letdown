#include "../common/callbacks.h"
#include "graphics/allocateVram.h"
#include "graphics/graphicsBoilerplate.h"

#include <pspuser.h>
#include <pspdebug.h>
#include <pspdisplay.h>

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

    while (running) {
        startFrame(); 

        endFrame(); 
    }

    termGraphics(); 

    // exit game, import from callbacks.c
    sceKernelExitGame();
    return EXIT_SUCCESS; 
}