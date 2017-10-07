#include "game_layer.h"

static const float SecondsPerFrame = (30.0f / 60.0f);

int32 
Game_Main()
{
	int32 WindowWidth = 1200;
	int32 WindowHeight = 800; 

	Platform_Initialize(WindowWidth, WindowHeight);
	Platform_InitRenderer();

	Render_Initialize();
	Platform_ShowWindow();

	Game_Initialization();

	// NOTE: Platform_Loop() calls Game_Loop() internally
	int32 Message = Platform_Loop();

	Render_PracticeCleanup();
	Platform_Cleanup();

	return Message;
}

void
Game_Initialization()
{
	Render_CompileShaders();
	Render_CreateRectangle();
	Render_CreateTexture();
}

void
Game_Loop()
{
	int64 LastCounter = Platform_GetCPUTimer();

	Render_PracticeDraw();

	// NOTE: Cap at 60FPS
	int64 CounterElapsed = Platform_GetCPUTimer() - LastCounter;
	float SecondsElapsedForFrame = ((float)CounterElapsed /
		(float)Platform_GetCPUTimerFrequency());
	while (SecondsElapsedForFrame < SecondsPerFrame)
	{
		SecondsElapsedForFrame = ((float)(Platform_GetCPUTimer() -
			LastCounter) / (float)Platform_GetCPUTimerFrequency());
	}

	LastCounter = Platform_GetCPUTimer();
}