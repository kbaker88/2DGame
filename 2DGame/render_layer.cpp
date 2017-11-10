#include "render_layer.h"

void
Render_Initialize()
{
	OpenGL_LoadFunctions();

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1200, 800);
}

uint32
Render_CompileShaders()
{
	uint32 VertexShader;
	VertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(VertexShader, 1, &VertexShaderString, 0);
	glCompileShader(VertexShader);

#if DEBUG_MODE
	int32 ErrorCheck;
	const uint32 BufferSize = 512;
	char ErrorCharBuffer[BufferSize]{};
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &ErrorCheck);
	if (!ErrorCheck)
	{
		glGetShaderInfoLog(VertexShader, BufferSize, 0,
			ErrorCharBuffer);
		Platform_ConsoleOutput(ErrorCharBuffer);
	}
#endif

	uint32 FragmentShader;
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &FragmentShaderString, 0);
	glCompileShader(FragmentShader);

#if DEBUG_MODE
	// NOTE: The buffer was never cleared, so if a previous error message
	// was in the buffer it will still be there and be overwritten.
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &ErrorCheck);
	if (!ErrorCheck)
	{
		glGetShaderInfoLog(FragmentShader, BufferSize, 0,
			ErrorCharBuffer);
		Platform_ConsoleOutput(ErrorCharBuffer);
	}
#endif

	uint32 ShaderProgram = glCreateProgram();

	glAttachShader(ShaderProgram, VertexShader);
#if DEBUG_MODE
	glGetProgramiv(ShaderProgram, GL_ATTACHED_SHADERS, &ErrorCheck);
	if (ErrorCheck == GL_FALSE)
	{
		glGetShaderInfoLog(ShaderProgram, BufferSize, 0,
			ErrorCharBuffer);
	}
#endif

	glAttachShader(ShaderProgram, FragmentShader);
#if DEBUG_MODE
	glGetProgramiv(ShaderProgram, GL_ATTACHED_SHADERS, &ErrorCheck);
	if (ErrorCheck == GL_FALSE)
	{
		glGetShaderInfoLog(ShaderProgram, BufferSize, 0,
			ErrorCharBuffer);
	}
#endif

	glLinkProgram(ShaderProgram);

#if DEBUG_MODE
	// NOTE: The buffer was never cleared, so if a previous error message
	// was in the buffer it will still be there and be overwritten.
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &ErrorCheck);
	if (!ErrorCheck)
	{
		glGetProgramInfoLog(ShaderProgram, BufferSize, 0,
			ErrorCharBuffer);
		Platform_ConsoleOutput(ErrorCharBuffer);
	}
#endif

	glDetachShader(ShaderProgram, VertexShader);
	glDetachShader(ShaderProgram, FragmentShader);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	return ShaderProgram;
}

uint32
Render_GetShaderVarID(uint32 ShaderProgramID, const char* VarName)
{
	return glGetUniformLocation(ShaderProgramID, VarName);
}

void
Render_CreateModel(Model* ModelChoice)
{
	uint32 VertexBufferObject[2]{};
	glCreateBuffers(2, VertexBufferObject);
	glNamedBufferStorage(VertexBufferObject[0], ModelChoice->VerticeByteSize,
		ModelChoice->VerticeData, 0);
	glNamedBufferStorage(VertexBufferObject[1], ModelChoice->TextCoordByteSize,
		ModelChoice->TextCoordData, 0);

	glCreateVertexArrays(1, &ModelChoice->VAOID);
	glVertexArrayVertexBuffer(ModelChoice->VAOID, 0,
		VertexBufferObject[0], 0, sizeof(float) * 3);
	glVertexArrayAttribFormat(ModelChoice->VAOID, 0, 3, GL_FLOAT,
		GL_FALSE, 0);
	glVertexArrayAttribBinding(ModelChoice->VAOID, 0, 0);
	glEnableVertexArrayAttrib(ModelChoice->VAOID, 0);

	glVertexArrayVertexBuffer(ModelChoice->VAOID, 1,
		VertexBufferObject[1], 0, sizeof(float) * 2);
	glVertexArrayAttribFormat(ModelChoice->VAOID, 1, 2, GL_FLOAT,
		GL_FALSE, 0);
	glVertexArrayAttribBinding(ModelChoice->VAOID, 1, 1);
	glEnableVertexArrayAttrib(ModelChoice->VAOID, 1);

	ModelChoice->VerticeBufferID = VertexBufferObject[0];
	ModelChoice->TextCoordBufferID = VertexBufferObject[1];
}

uint32
Render_CreateTexture(Texture* TextureChoice)
{
	uint32 TextureID;
#if OPENGL_4_5
	glCreateTextures(GL_TEXTURE_2D, 1, &TextureID);

	if (TextureChoice->BytesPerPixel == 3)
	{
		glTextureStorage2D(TextureID, 1, GL_RGB8, TextureChoice->Width,
			TextureChoice->Height);
		glTextureSubImage2D(TextureID, 0, 0, 0,
			TextureChoice->Width, TextureChoice->Height,
			GL_RGB, GL_UNSIGNED_BYTE, TextureChoice->Data);
	}
	else if (TextureChoice->BytesPerPixel == 4)
	{
		glTextureStorage2D(TextureID, 1, GL_RGBA8, TextureChoice->Width,
			TextureChoice->Height);
		glTextureSubImage2D(TextureID, 0, 0, 0,
			TextureChoice->Width, TextureChoice->Height,
			GL_RGBA, GL_UNSIGNED_BYTE, TextureChoice->Data);
	}

	glTextureParameteri(TextureID, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);
	glTextureParameteri(TextureID, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);

#else
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	if (TextureChoice->BytesPerPixel == 3)
	{
		//glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, ImageWidth,
		//	ImageHeight);
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
		//	ImageWidth, ImageHeight,
		//	GL_RGB, GL_UNSIGNED_BYTE, ImageData);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureChoice->Width, 
			TextureChoice->Height, 0, GL_RGB, GL_UNSIGNED_BYTE,
			TextureChoice->Data);
	}
	else if (TextureChoice->BytesPerPixel == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureChoice->Width,
			TextureChoice->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
			TextureChoice->Data);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
		return TextureID;
}

void
Render_UpdateShaderVar(uint32 VarID, float* Data)
{
	glUniformMatrix4fv(VarID, 1, 0, Data);
}

void
Render_UseShader(uint32 ShaderProgramID)
{
#if DEBUG_MODE
	GLint status;
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		Platform_ConsoleOutput("Error in compiling the ShaderProgramHandle\n");
	}
	else
	{
		glUseProgram(ShaderProgramID);
	}
#else
	glUseProgram(ShaderProgramID);
#endif
}

void
Render_ClearScreen()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
Render_Draw(Model* ModelChoice, uint32 TextureID)
{
#if OPENGL_4_5
	glBindTextureUnit(0, TextureID);
#else
	glBindTexture(GL_TEXTURE_2D, TextureID);
#endif

	glBindVertexArray(ModelChoice->VAOID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

#if OPENGL_4_5
	glBindTextureUnit(0, 0);
#else
	glBindTexture(GL_TEXTURE_2D, 0);
#endif
}

void
Render_PracticeCleanup(uint32 TextureID, uint8* TextureData,
	uint32 VertexArrayObj, uint32 VBO1, 
	uint32 VBO2, uint32 ShaderProgramID)
{

	glDeleteTextures(1, &TextureID);
	if (TextureData)
	{
		delete[] TextureData;
	}
	glUseProgram(0);
	glDeleteProgram(ShaderProgramID);
	glDeleteVertexArrays(1, &VertexArrayObj);
	glDeleteBuffers(1, &VBO1);
	glDeleteBuffers(1, &VBO2);
}