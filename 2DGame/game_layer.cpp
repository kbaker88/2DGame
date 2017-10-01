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

	int32 Message = Platform_Loop();

	Platform_Cleanup();
	return Message;
}

void
Game_Loop()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}