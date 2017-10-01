#include "render_layer.h"

static uint32 ShaderProgram = 0;
static uint32 VertexBufferObject = 0;
static uint32 VertexArrayObject = 0;

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
		glGetShaderInfoLog(VertexShader, BufferSize, 0, ErrorCharBuffer);
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
		glGetShaderInfoLog(FragmentShader, BufferSize, 0, ErrorCharBuffer);
		Platform_ConsoleOutput(ErrorCharBuffer);
	}
#endif

	ShaderProgram = glCreateProgram();

	glAttachShader(ShaderProgram, VertexShader);
#if DEBUG_MODE
	glGetProgramiv(ShaderProgram, GL_ATTACHED_SHADERS, &ErrorCheck);
	if (ErrorCheck == GL_FALSE)
	{
		glGetShaderInfoLog(ShaderProgram, BufferSize, 0, ErrorCharBuffer);
	}
#endif

	glAttachShader(ShaderProgram, FragmentShader);
#if DEBUG_MODE
	glGetProgramiv(ShaderProgram, GL_ATTACHED_SHADERS, &ErrorCheck);
	if (ErrorCheck == GL_FALSE)
	{
		glGetShaderInfoLog(ShaderProgram, BufferSize, 0, ErrorCharBuffer);
	}
#endif

	glLinkProgram(ShaderProgram);

#if DEBUG_MODE
	// NOTE: The buffer was never cleared, so if a previous error message
	// was in the buffer it will still be there and be overwritten.
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &ErrorCheck);
	if (!ErrorCheck)
	{
		glGetProgramInfoLog(ShaderProgram, BufferSize, 0, ErrorCharBuffer);
		Platform_ConsoleOutput(ErrorCharBuffer);
	}
#endif

	glDetachShader(ShaderProgram, VertexShader);
	glDetachShader(ShaderProgram, FragmentShader);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
	
	/***************
	 TRIANGLE SETUP
	****************/

	GLfloat Vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	glPointSize(10.0f);

	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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

	glBindVertexArray(VertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void
Render_PracticeCleanup()
{
	glUseProgram(0);
	glDeleteProgram(ShaderProgram);
	glDeleteVertexArrays(1, &VertexArrayObject);
	glDeleteBuffers(1, &VertexBufferObject);
}