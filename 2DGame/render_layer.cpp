#include "render_layer.h"

static uint32 ShaderProgram = 0;
static uint32 VertexBufferObject[2]{};
static uint32 VertexArrayObject = 0;
static uint32 TextureIDs[11]{};
static uint32 ShaderUniform[4]{};
uint8* ImageData = 0;
static uint32 LoopIndex = 0;

static m4 ViewMatrix;
static m4 ProjectionMatrix;
static m4 ModelMatrix;

void
Render_Initialize()
{
	OpenGL_LoadFunctions();

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1200, 800);
	v3 CameraPosition = v3(0.0f, 0.0f, 2.0f);
	v3 CameraTarget = v3(0.0f, 0.0f, -1.0f);
	v3 UpDirection = v3(0.0f, 1.0f, 0.0f);
//	ProjectionMatrix = Math_OrthographicMarix(0.0f, 1200.0f, 0.0f, 800.0f, 0.1f, 100.0f);
	ProjectionMatrix = Math_PerspectiveMatrix(45.0f, 1200 / 800, 0.01f, 1000.0f);
	ViewMatrix = Math_LookAtMatrix(CameraPosition,
		v3(0.0f, 0.0f, 0.0f), UpDirection);
}

void
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

	ShaderProgram = glCreateProgram();

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

	ShaderUniform[0] = glGetUniformLocation(ShaderProgram, "view");
	ShaderUniform[1] = glGetUniformLocation(ShaderProgram, "projection");
	ShaderUniform[2] = glGetUniformLocation(ShaderProgram, "model");
	ShaderUniform[3] = glGetUniformLocation(ShaderProgram, "TextureData");
}

void
Render_CreateRectangle()
{
	float Vertices[] = {
		-0.1f, -0.1f, 0.0f,
		 0.1f, -0.1f, 0.0f,
		 0.1f,  0.1f, 0.0f,

		 0.1f,  0.1f, 0.0f,
		-0.1f,  0.1f, 0.0f,
		-0.1f, -0.1f, 0.0f
	};

	float TextureCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

#if OPENGL_4_5
	glCreateBuffers(2, VertexBufferObject);
	glNamedBufferStorage(VertexBufferObject[0], sizeof(Vertices),
		Vertices, 0);
	glNamedBufferStorage(VertexBufferObject[1], sizeof(TextureCoords),
		TextureCoords, 0);

	glCreateVertexArrays(1, &VertexArrayObject);
	glVertexArrayVertexBuffer(VertexArrayObject, 0,
		VertexBufferObject[0], 0, sizeof(float) * 3);
	glVertexArrayAttribFormat(VertexArrayObject, 0, 3, GL_FLOAT,
		GL_FALSE, 0);
	glVertexArrayAttribBinding(VertexArrayObject, 0, 0);
	glEnableVertexArrayAttrib(VertexArrayObject, 0);

	glVertexArrayVertexBuffer(VertexArrayObject, 1,
		VertexBufferObject[1], 0, sizeof(float) * 2);
	glVertexArrayAttribFormat(VertexArrayObject, 1, 2, GL_FLOAT,
		GL_FALSE, 0);
	glVertexArrayAttribBinding(VertexArrayObject, 1, 1);
	glEnableVertexArrayAttrib(VertexArrayObject, 1);
#else
	glGenBuffers(2, VertexBufferObject);

	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices),
		Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TextureCoords),
		TextureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		2 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
#endif
	ModelMatrix = Math_TranslateMatrix(&Math_IdentityMatrix(),
		&v3(0.0f, 0.0f, 0.0f));
}

void
Render_CreateTexture()
{
	uint32 ImageWidth = 0;
	uint32 ImageHeight = 0;
	uint8* ImageData = 0;

	char* ImageFileName[11] = {"images/Simple-warrior1.bmp", "images/Simple-warrior2.bmp", 
		"images/Simple-warrior3.bmp", "images/Simple-warrior4.bmp", "images/Simple-warrior5.bmp",
		"images/Simple-warrior6.bmp", "images/Simple-warrior7.bmp", "images/Simple-warrior8.bmp",
		"images/Simple-warrior9.bmp", "images/Simple-warrior10.bmp", "images/Simple-warrior11.bmp" };

//	char* ImageFileName = "images/Tree-Logo.bmp";

	for (uint32 Index = 0; Index < 11; Index++)
	{

#if OPENGL_4_5
	glCreateTextures(GL_TEXTURE_2D, 1, &TextureIDs[Index]);

#if DEBUG_MODE
		if (!Platform_DoesFileExist(ImageFileName[Index]))
		{
			Platform_ConsoleOutput("File Not Found.\n");
		}
#endif

		uint8 BytesPerPixel = 0;
		uint8* FileData = Platform_ReadFile(ImageFileName[Index]);
		BMP_ExtractImageData(FileData, &ImageData, &ImageWidth,
			&ImageHeight, &BytesPerPixel);

		if (FileData)
		{
			delete[] FileData;
		}
		glCreateTextures(GL_TEXTURE_2D, 1, &TextureIDs[Index]);

		if (BytesPerPixel == 3)
		{
			glTextureStorage2D(TextureIDs[Index], 1, GL_RGB8, ImageWidth,
				ImageHeight);
			glTextureSubImage2D(TextureIDs[Index], 0, 0, 0,
				ImageWidth, ImageHeight,
				GL_RGB, GL_UNSIGNED_BYTE, ImageData);
		}
		else if (BytesPerPixel == 4)
		{
			glTextureStorage2D(TextureIDs[Index], 1, GL_RGBA8, ImageWidth,
				ImageHeight);
			glTextureSubImage2D(TextureIDs[Index], 0, 0, 0,
				ImageWidth, ImageHeight,
				GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
		}

		glTextureParameteri(TextureIDs[Index], GL_TEXTURE_MIN_FILTER,
			GL_NEAREST);
		glTextureParameteri(TextureIDs[Index], GL_TEXTURE_MAG_FILTER,
			GL_NEAREST);

	}

#else
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	if (BytesPerPixel == 3)
	{
		//glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, ImageWidth,
		//	ImageHeight);
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
		//	ImageWidth, ImageHeight,
		//	GL_RGB, GL_UNSIGNED_BYTE, ImageData);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ImageData);
	}
	else if (BytesPerPixel == 4)
	{
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, ImageWidth,
			ImageHeight);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
			ImageWidth, ImageHeight,
			GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif

}

void
Render_PracticeDraw()
{
	if (LoopIndex >= 11)
	{
		LoopIndex = 0;
	}
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if DEBUG_MODE
	GLint status;
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		Platform_ConsoleOutput("Error in compiling the ShaderProgramHandle\n");
	}
	else
	{
		glUseProgram(ShaderProgram);
	}
#else
	glUseProgram(ShaderProgram);
#endif

	glUniformMatrix4fv(ShaderUniform[0], 1, 0, (float*)&ViewMatrix);
	glUniformMatrix4fv(ShaderUniform[1], 1, 0, (float*)&ProjectionMatrix);
	glUniformMatrix4fv(ShaderUniform[2], 1, 0, (float*)&ModelMatrix);
	//glUniform1i(TextureShaderPosition, 0);

#if OPENGL_4_5
	glBindTextureUnit(0, TextureIDs[LoopIndex]);
#else
	glBindTexture(GL_TEXTURE_2D, TextureID);
#endif

	glBindVertexArray(VertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

#if OPENGL_4_5
	glBindTextureUnit(0, 0);
#else
	glBindTexture(GL_TEXTURE_2D, 0);
#endif

	LoopIndex++;
}

void
Render_PracticeCleanup()
{
	for (uint32 i = 0; i < 11; i++)
	{
		glDeleteTextures(1, &TextureIDs[i]);
	}
	if (ImageData)
	{
		delete[] ImageData;
	}
	glUseProgram(0);
	glDeleteProgram(ShaderProgram);
	glDeleteVertexArrays(1, &VertexArrayObject);
	glDeleteBuffers(2, VertexBufferObject);
}