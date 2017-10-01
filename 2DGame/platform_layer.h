#ifndef PLATFORM_LAYER_H
#define PLATFORM_LAYER_H

#include <Windows.h>

#define DEBUG_MODE 1

typedef int int32;
typedef unsigned int uint32;

void 
Platform_Initialize(int32 WindowWidth, int32 WindowHeight);
void
Platform_InitRenderer();
void
Platform_ShowWindow();
int32
Platform_Loop();
void
Platform_Cleanup();


#endif