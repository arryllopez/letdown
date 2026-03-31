#include "allocateVram.h"

#include <stdlib.h>
#include <pspge.h>
#include <pspgu.h>

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
        case GU_PSM_4444:
            // if this is using 4 r 4 g 4 b 4 a
            return size * 2;
        case GU_PSM_T16:
            return size * 2;
        case GU_PSM_8888:
        case GU_PSM_T32:
            return size * 4;
        default:
            // must indicate a psm type or image wont even render at all
            return EXIT_FAILURE;
    }
}

void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm) {
    static unsigned int staticOffset = 0;
    unsigned int memSize = getMemorySize(width, height, psm);
    void* result = (void*)staticOffset;
    staticOffset += memSize;
    return result;
}

void* getVramTexture(unsigned int width, unsigned int height, unsigned int psm) {
    void* result = getStaticVramBuffer(width, height, psm);
    return (void*)((unsigned int)result + (unsigned int)sceGeEdramGetAddr());
}