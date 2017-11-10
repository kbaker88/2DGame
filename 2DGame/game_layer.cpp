#include "game_layer.h"

static const float SecondsPerFrame = (10.0f / 60.0f);

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

	TestZone_Cleanup();
	Platform_Cleanup();

	return Message;
}

void
Game_Initialization()
{

}

static bool T_ZoneLoaded = false;

void
Game_Loop()
{
	int64 LastCounter = Platform_GetCPUTimer();
	Render_ClearScreen();

	if (T_ZoneLoaded == false)
	{
		TestZone_Load();
		T_ZoneLoaded = true;
	}
	else
	{
		TestZone_Loop();
	}

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