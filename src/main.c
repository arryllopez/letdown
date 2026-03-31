#include "../common/callbacks.h"
#include "graphics/allocateVram.h"

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
// GE List, this is basically where the sceGu commands are stored before being sent to the GE, this is required for rendering
static unsigned int __attribute__((aligned(16))) list [262144];

void initGraphics() { 
    void* fbp0 = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_8888); //back buffer, this is where the GE will render to before it is sent to the display
    void* fbp1 = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_8888); //front buffer, this is where the GE will send the rendered image to be displayed on the screen
    void* zbp = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_4444); //depth buffer, this is where the GE will store depth information for 3D rendering, this is required for 3D rendering but not used in this example

    sceGuInit();
    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888, fbp0, PSP_BUF_WIDTH);
    sceGuDispBuffer(PSP_SCR_WIDTH, PSP_SCR_HEIGHT, fbp1, PSP_BUF_WIDTH);
    sceGuDepthBuffer(zbp, PSP_BUF_WIDTH);
}

int main()
{ 
    SetupCallbacks(); 

    // im pretty sure i have a psp 1000 but in 2000+ models have 4 mb of vram compared to 2 mb in the 1000. 
    sceGeEdramSetSize();

    while (running) {
        // Game loop logic here
    }

    // exit game, import from callbacks.c
    sceKernelExitGame();
    return EXIT_SUCCESS; 
}