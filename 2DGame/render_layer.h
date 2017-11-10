#ifndef RENDER_LAYER_H
#define RENDER_LAYER_H

// NOTE: Warning! DO NOT put opengl.h before platform_layer.h.
// Doing so will result in errors. Windows.h must be called before OpenGL libraries

#include "platform_layer.h"
#include "opengl.h"
#include "math.h"
#include "shaders.h"
#include "model_system.h"
#include "asset_system.h"

void
Render_Initialize();
void
OpenGL_LoadFunctions();
void
Render_ClearScreen();
void
Render_CreateModel(Model* ModelChoice);
uint32
Render_GetShaderVarID(uint32 ShaderProgramID, const char* VarName);
void
Render_UpdateShaderVar(uint32 VarID, float* Data);
uint32
Render_CompileShaders();
void
Render_UseShader(uint32 ShaderProgramID);
uint32
Render_CreateTexture(Texture* TextureChoice);
void
Render_Draw(Model* ModelChoice, uint32 TextureID);
void
Render_PracticeCleanup(uint32 TextureID, uint8* TextureData,
	uint32 VertexArrayObj, uint32 VBO1,
	uint32 VBO2, uint32 ShaderProgramID);
#endif
