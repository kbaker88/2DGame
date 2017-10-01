#include "game_layer.h"

int32 
Game_Main()
{
	int32 WindowWidth = 1200;
	int32 WindowHeight = 800; 

	Platform_Initialize(WindowWidth, WindowHeight);
	Platform_InitRenderer();

	glViewport(0, 0, WindowWidth, WindowHeight);

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
	Render_Practice();
}

void
Game_Loop()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Render_PracticeDraw();
}