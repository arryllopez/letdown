#include <pspkernel.h>
#include <psppower.h>
#include <oslib/oslib.h>

#include "engine/core/game_loop.h"

PSP_MODULE_INFO("letdown", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-1024);

// Callback so the OS can tell us to quit
int exitCallback(int arg1, int arg2, void* common) {
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void* argp) {
    int cbid = sceKernelCreateCallback("ExitCB", exitCallback, nullptr);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

void setupCallbacks() {
    int thid = sceKernelCreateThread("cbThread", callbackThread,
                                      0x11, 0xFA0, 0, nullptr);
    if (thid >= 0) sceKernelStartThread(thid, 0, nullptr);
}

int main() {
    setupCallbacks();
    scePowerSetClockFrequency(333, 333, 166);

    // Initialize OSLib
    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    oslInitConsole();
    oslInitAudio();

    // Hand off to the game loop
    engine::GameLoop loop;
    loop.run();

    // Teardown
    oslEndGfx();
    oslQuit();
    sceKernelExitGame();
    return 0;
}
