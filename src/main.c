#include "../common/callbacks.h"

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
// GE List, this is basically where the sceGu commands are stored before being sent to the GPU, this is required for rendering
static unsigned int __attribute__((aligned(16))) list [262144];

/*
Each case basically describes the amount of bits allocated per color channel
This function will calcualte how much memory in bytes a texture/image needs
where width * height is the total number of pixels it has and psm is the pixel storage mode 
psm is passed in based on the desired psm and switched to return the proper amount of bytes the 
image/texture needs. 
*/

static unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm) { 
    unsigned int size = width * height;  //total pixel size of the texture/image
    switch (psm) { 
        case GU_PSM_T4: 
            return size / 2; 
        case GU_PSM_T8: 
            return size; 
        case GU_PSM_5650: 
        case GU_PSM_5551: 
        case GU_PSM_4444: // if this is using 4 r 4 g 4 b 4 a 
            return size * 2;
        case GU_PSM_T16:
            return size * 2;
        case GU_PSM_8888: 
        case GU_PSM_T32; 
            return size * 4; 
        default: 
            return EXIT_FAILURE; // must indicate a psmt ype or image wont even render at all 
    }
}

int main()
{ 
    SetupCalbacks(); 

    // im pretty sure i have a psp 1000 but in 2000+ models have 4 mb of vram compared to 2 mb in the 1000. 
    sceGeEdramSetSize()

    while (running) {
        // Game loop logic here
    }

    // exit game, import from callbacks.c
    sceKernelExitGame();
    return EXIT_SUCCESS; 
}