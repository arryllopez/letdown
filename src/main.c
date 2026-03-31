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

// Function Initializes the graphics system 
void initGraphics() { 
    // Initializing frame, depth and back buffer 
    // Frame buffer is where the final image is drawn to, this is what is displayed on the screen
    // Depth buffer is where the depth information of each pixel is stored, this is used for
    // Back buffer is where the next frame is drawn to, this is used for double buffering, this is required for rendering to work properly
    void* fbp0 = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_8888); 
    void* fbp1 = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_8888); 
    void* zbp = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_4444); 

    sceGuInit();
    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888, fbp0, PSP_BUF_WIDTH);
    sceGuDispBuffer(PSP_SCR_WIDTH, PSP_SCR_HEIGHT, fbp1, PSP_BUF_WIDTH);
    sceGuDepthBuffer(zbp, PSP_BUF_WIDTH);

    sceGuOffset(2048 - (PSP_SCR_WIDTH / 2), 2048 - (PSP_SCR_HEIGHT / 2)); //drawing in the middle of the screen
    sceGuViewport(2048, 2048, PSP_SCR_WIDTH, PSP_SCR_HEIGHT); // setting the viewport to the size of the screen, this is required for rendering to work properly
    sceGuDepthRange(65535,0); // the psp has an inverted depth buffer, this means that the near plane is at 65535 and the far plane is at 0, this is required for 3D rendering 
    
    sceGuEnable(GU_SCISSOR_TEST); // enabling scissor test, this is required for rendering to work properly
    sceGuScissor(0, 0, PSP_SCR_WIDTH, PSP_SCR_HEIGHT); // setting the scissor to the size of the screen, this is required for rendering to work properly
    
    sceGuEnable(GU_DEPTH_TEST); // enabling depth test, this is required for 3D rendering
    sceGuDepthFunc(GU_GEQUAL); // setting the depth function to greater than or equal, this is required for 3D rendering
    
    sceGuEnable(GU_CULL_FACE); // enabling cull face, this is required for 3D rendering
    sceGuFrontFace(GU_CW); // setting the front face to clockwise, this is required for 3D rendering
    
    sceGuShadeModel(GU_SMOOTH); // setting the shade model to smooth, this is required for 3D rendering
    sceGuEnable(TEXTURE_2D); // allowing textures on objects 
    sceGuEnable(GU_CLIP_PLANES); // enabling clip planes, this is required for 3D rendering

    sceGuFinish(); 
    sceGuSync(0,0); 
    
    sceGuDisplayWaitVblankStart(); // waiting for the vertical blank, this is required for rendering to work properly
    sceGuDisplay(GU_TRUE); // enabling the display, this is required for rendering to 
}

void termGraphics() { 
    sceGuTerm(); 
}

void 

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