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

/*For the latch method, uiMake and uiBreak fields are used. When any number of keys have been pressed at once, 
uiMake will update from 0 to the bit-booleans of all the keys pressed for only that frame. When a any number of keys have been released at once, 
uiBreak will update from 0 to the bit-booleans of all the keys released for only that frame. If the keys 1011 were held at once, uiMake will be 1011 and in the next frame, 
if no other keys were pressed, be 0000. If only the key 0010 was released in a following frame, uiBreak will be 0010 and the following frame, 
if no other keys were released, will be 0000. If the keys 1001 were released together in a following frame, uiBreak will be 1001. Proper functions would be isKeyDown() and isKeyUp(). 
*/ 

int isKeyDown (int key) { 
    return latch.uiMake & key; 
}

int isKeyUp (int key) { 
    return latch.uiBreak & key; 
}


