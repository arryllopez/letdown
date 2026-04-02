#include <pspctrl.h> 

static SceCtrlData data; 
static SceCtrlLatch latch; 

// Joystick functions (x.y) 
int getJX() { 
    return data.Lx; 
}

int getJY() { 
    return data.Ly; 
}

// This function will query the hardware once per frame when called. 
// &data has the following values 
// int TimeStamp, int Buttons int Lx and int Ly 

void pollPad() { 
    sceCtrlReadBufferPositive(&data, 1);
}

// The latch struct has th efollowing 
// uiMake, uiBreak, uiPress, uiRelease
void pollLatch() { 
    sceCtrlReadLatch(&latch); // pointer to the latch struct
}

// Helpers for holding methods that will be used in the main game loop to check for button presses, releases, etc. 
int isKeyHold (int key) { 
    return latch.uiPress & key; 
}

