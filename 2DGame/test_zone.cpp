#include "test_zone.h"

Camera PlayerCamera;
Model* TestRect;
uint32 ShaderVarIDArr[4]{};
uint32 ShaderProgramID, TestTextureID;
m4 ModelMatrix;
Texture* TestTexture;

void TestZone_Load()
{
	Camera_SetProjection(&PlayerCamera, 1200,
		800, &v3(0.0f, 0.0f, 5.0f));

	ShaderProgramID = Render_CompileShaders();

	ShaderVarIDArr[0] = Render_GetShaderVarID(ShaderProgramID, "view");
	ShaderVarIDArr[1] = Render_GetShaderVarID(ShaderProgramID, "projection");
	ShaderVarIDArr[2] = Render_GetShaderVarID(ShaderProgramID, "model");
	ShaderVarIDArr[3] = Render_GetShaderVarID(ShaderProgramID, "TextureData");

	TestRect = Model_CreateRect();
	Render_CreateModel(TestRect);

	TestTexture = Asset_LoadTexture("images/Simple-warriorTest.bmp\0");
	TestTextureID = Render_CreateTexture(TestTexture);
}

void TestZone_Loop()
{
	Render_UseShader(ShaderProgramID);

	ModelMatrix = Math_TranslateMatrix(&Math_IdentityMatrix(),
		&v3(0.0f, 0.0f, 0.0f));

	Render_UpdateShaderVar(ShaderVarIDArr[0], (float*)&PlayerCamera.ViewMatrix);
	Render_UpdateShaderVar(ShaderVarIDArr[1], (float*)&PlayerCamera.ProjectionMatrix);
	Render_UpdateShaderVar(ShaderVarIDArr[2], (float*)&ModelMatrix);

	Render_Draw(TestRect, TestTextureID);
}

void TestZone_Cleanup()
{
	Render_PracticeCleanup(TestTextureID, TestTexture->Data,
		TestRect->VAOID, TestRect->VerticeBufferID,
		TestRect->TextCoordBufferID, ShaderProgramID);
}