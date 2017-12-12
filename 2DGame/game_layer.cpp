#include "game_layer.h"

static const 
float SecondsPerFrame = (10.0f / 60.0f);

typedef void
ZoneVoidFunction();

typedef int32
ZoneIntFunction();

typedef int64
WindowsMsgHandle(void* Window, uint32 Message,
	uint64 wParam, int64 lParam);

struct 
ZoneState
{
	ZoneVoidFunction* Load;
	ZoneVoidFunction* Run;
	ZoneIntFunction* Status;
	ZoneVoidFunction* Clean;
	WindowsMsgHandle* MsgHandle;
};

ZoneState ZoneStates[1];

int32 
Game_Main()
{
	int32 WindowWidth = 1200;
	int32 WindowHeight = 800; 

	Platform_Initialize(WindowWidth, WindowHeight);
	Platform_InitRenderer();

	Render_Initialize();
	Platform_ShowWindow();

	ZoneStates[0].Load = (ZoneVoidFunction*)Zone_1_Load;
	ZoneStates[0].Run = (ZoneVoidFunction*)Zone_1_Run;
	ZoneStates[0].Status = (ZoneIntFunction*)Zone_1_Status;
	ZoneStates[0].Clean = (ZoneVoidFunction*)Zone_1_Cleanup;
	ZoneStates[0].MsgHandle =
		(WindowsMsgHandle*)Zone_1_MsgHandle;

	// NOTE: Platform_Loop() calls Game_Loop() internally
	int32 Message = Platform_Loop();

	//TestZone_Cleanup();
	Platform_Cleanup();

	return Message;
}

static
bool T_ZoneLoaded = false;

void
Game_Loop()
{
	int64 LastCounter = Platform_GetCPUTimer();
	Render_ClearScreen();

	uint32 CurrentState = 0;
	if (ZoneStates[CurrentState].Status() == 1)
	{
		ZoneStates[CurrentState].Run();
	}
	else if (ZoneStates[CurrentState].Status() == 0)
	{
		ZoneStates[CurrentState].Load();
	}
	else
	{
		ZoneStates[CurrentState].Clean();
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