#ifndef PLATFORM_LAYER_H
#define PLATFORM_LAYER_H

#include <Windows.h>

#define DEBUG_MODE 1

typedef signed char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int  uint32;
typedef long long int64;
typedef unsigned long long uint64;

void 
Platform_Initialize(int32 WindowWidth, int32 WindowHeight);
void
Platform_InitRenderer();
void
Platform_ShowWindow();
int32
Platform_Loop();
void
Platform_ConsoleOutput(char* Text);
int64
Platform_GetCPUTimerFrequency();
int64
Platform_GetCPUTimer();
int8
Platform_DoesFileExist(char* FileName);
unsigned char*
Platform_ReadFile(char* FileName);
int8
Platform_GetStateOfKey(int key);
void
Platform_Cleanup();


#endif 