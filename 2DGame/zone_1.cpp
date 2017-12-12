#include "zone_1.h"

Camera PlayerCamera;
//Model* TestRect;
Model* PlayerRect;
Model* EnvironRect;
uint32 ShaderVarIDArr[4]{};
uint32 ShaderProgramID, TestTextureID;
m4 ModelMatrix_Player;
m4 ModelMatrix_WorldObj;
//Texture* TestTexture;
Texture* Texture_Player[5];
Texture* Texture_Floor[5];
Texture* Texture_Chest[4];
Texture* Texture_Bricks[1];
Texture* Texture_Stone[3];

uint32 TextureID_Player[5];
uint32 TextureID_Floor[5];
uint32 TextureID_Chest[4];
uint32 TextureID_Bricks[1];
uint32 TextureID_Stone[3];

int32 ZoneStatus = 0;

void
Zone_1_Load()
{
	Camera_SetProjection(&PlayerCamera, 1200,
		800, &v3(0.0f, 0.0f, 5.0f));

	ShaderProgramID = Render_CompileShaders();

	ShaderVarIDArr[0] = Render_GetShaderVarID(ShaderProgramID, "view");
	ShaderVarIDArr[1] = Render_GetShaderVarID(ShaderProgramID, "projection");
	ShaderVarIDArr[2] = Render_GetShaderVarID(ShaderProgramID, "model");
	ShaderVarIDArr[3] = Render_GetShaderVarID(ShaderProgramID, "TextureData");

	PlayerRect = Model_CreateRect();
	Render_CreateModel(PlayerRect);

	EnvironRect = Model_CreateRect();
	Render_CreateModel(EnvironRect);

	Texture_Player[0] = Asset_LoadTexture("images/Simple-warriorTest.bmp\0");
	TextureID_Player[0] = Render_CreateTexture(Texture_Player[0]);

	ZoneStatus = 1;
}

void
Zone_1_Run()
{
	Render_UseShader(ShaderProgramID);

	Render_UpdateShaderVar(ShaderVarIDArr[0], (float*)&PlayerCamera.ViewMatrix);
	Render_UpdateShaderVar(ShaderVarIDArr[1], (float*)&PlayerCamera.ProjectionMatrix);

	ModelMatrix_Player = Math_TranslateMatrix(&Math_IdentityMatrix(),
		&v3(0.0f, 0.0f, 0.0f));

	Render_UpdateShaderVar(ShaderVarIDArr[2], (float*)&ModelMatrix_Player);
	Render_Draw(PlayerRect, TextureID_Player[0]);
}

int32
Zone_1_Status()
{
	return ZoneStatus;
}

void
Zone_1_Cleanup()
{
	Render_PracticeCleanup(TestTextureID, Texture_Player[0]->Data,
		PlayerRect->VAOID, PlayerRect->VerticeBufferID,
		PlayerRect->TextCoordBufferID, ShaderProgramID);

	ZoneStatus = 0;
}

int64
Zone_1_MsgHandle(void* Window, uint32 Message,
	uint64 wParam, int64 lParam)
{

	return 0;
}