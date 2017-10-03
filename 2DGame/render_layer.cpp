#include "render_layer.h"

static uint32 ShaderProgram = 0;
static uint32 VertexBufferObject[2]{};
static uint32 VertexArrayObject = 0;
static uint32 TextureID;

void
Render_Initialize()
{
	OpenGL_LoadFunctions();

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1200, 800);
}

void
Render_Practice()
{
	/**************
	  SHADER SETUP
	***************/
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
	
	/***************
	 RECTANGLE SETUP
	****************/

	float Vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f, 

		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	float TextureCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

	glCreateBuffers(2, VertexBufferObject);
	glNamedBufferStorage(VertexBufferObject[0], sizeof(Vertices),
		Vertices, 0);
	glNamedBufferStorage(VertexBufferObject[1], sizeof(TextureCoords),
		TextureCoords, 0);

	glCreateVertexArrays(1, &VertexArrayObject);
	glVertexArrayVertexBuffer(VertexBufferObject[0], 0, 
		VertexBufferObject[0], 0, sizeof(float) * 3);
	glVertexArrayAttribFormat(VertexBufferObject[0], 0, 3, GL_FLOAT, 
		GL_FALSE, 0);
	glVertexArrayAttribBinding(VertexArrayObject, 0, 0);
	glEnableVertexArrayAttrib(VertexArrayObject, 0);

	glVertexArrayVertexBuffer(VertexBufferObject[1], 1,
		VertexBufferObject[0], 0, sizeof(float) * 3);
	glVertexArrayAttribFormat(VertexBufferObject[1], 1, 3, GL_FLOAT,
		GL_FALSE, 0);
	glVertexArrayAttribBinding(VertexArrayObject, 1, 1);
	glEnableVertexArrayAttrib(VertexArrayObject, 1);



	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID); 
										
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	uint32 ImageWidth = 0;
	uint32 ImageHeight = 0;
	uint8* ImageData = 0;
	uint8* FileData = Platform_ReadFile("images/test_image.bmp");
	BMP_ExtractImageData(FileData, ImageData, &ImageWidth,
		&ImageHeight);
	delete[] FileData;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0,
		GL_RGB, GL_UNSIGNED_BYTE, ImageData);
	//glGenerateMipmap(GL_TEXTURE_2D);
	delete[] ImageData;

	/*****************
		  OLD CODE
	******************/

	//GLfloat Vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f, 0.5f, 0.0f
	//};

	//glGenBuffers(1, &VertexBufferObject);
	//glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	//glGenVertexArrays(1, &VertexArrayObject);
	//glBindVertexArray(VertexArrayObject);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}

void
Render_PracticeDraw()
{
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

	glBindTexture(GL_TEXTURE_2D, TextureID);
	glBindVertexArray(VertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void
Render_PracticeCleanup()
{
	glUseProgram(0);
	glDeleteProgram(ShaderProgram);
	glDeleteVertexArrays(1, &VertexArrayObject);
	glDeleteBuffers(2, VertexBufferObject);
}