#include "render_layer.h"

// OpenGL 2
static gl_create_shader *glCreateShader;
static gl_shader_source *glShaderSource;
static gl_compile_shader *glCompileShader;
static gl_get_shader_iv *glGetShaderiv;
static gl_create_program *glCreateProgram;
static gl_attach_shader *glAttachShader;
static gl_link_program *glLinkProgram;
static gl_detach_shader *glDetachShader;
static gl_delete_shader *glDeleteShader;
static gl_get_shader_info_log *glGetShaderInfoLog;
static gl_get_program_iv *glGetProgramiv;
static gl_use_program *glUseProgram;
static gl_get_uniform_location *glGetUniformLocation;
static gl_uniform_1i *glUniform1i;
static gl_uniform_2i *glUniform2i;
static gl_uniform_3i *glUniform3i;
static gl_uniform_4i *glUniform4i;
static gl_uniform_1iv *glUniform1iv;
static gl_uniform_2iv *glUniform2iv;
static gl_uniform_3iv *glUniform3iv;
static gl_uniform_4iv *glUniform4iv;
static gl_uniform_1ui *glUniform1ui;
static gl_uniform_2ui *glUniform2ui;
static gl_uniform_3ui *glUniform3ui;
static gl_uniform_4ui *glUniform4ui;
static gl_uniform_1uiv *glUniform1uiv;
static gl_uniform_2uiv *glUniform2uiv;
static gl_uniform_3uiv *glUniform3uiv;
static gl_uniform_4uiv *glUniform4uiv;
static gl_uniform_1f *glUniform1f;
static gl_uniform_2f *glUniform2f;
static gl_uniform_3f *glUniform3f;
static gl_uniform_4f *glUniform4f;
static gl_uniform_1fv *glUniform1fv;
static gl_uniform_2fv *glUniform2fv;
static gl_uniform_3fv *glUniform3fv;
static gl_uniform_4fv *glUniform4fv;
static gl_uniform_matrix_2fv *glUniformMatrix2fv;
static gl_uniform_matrix_3fv *glUniformMatrix3fv;
static gl_uniform_matrix_4fv *glUniformMatrix4fv;
static gl_uniform_matrix_2x3fv *glUniformMatrix2x3fv;
static gl_uniform_matrix_3x2fv *glUniformMatrix3x2fv;
static gl_uniform_matrix_2x4fv *glUniformMatrix2x4fv;
static gl_uniform_matrix_4x2fv *glUniformMatrix4x2fv;
static gl_uniform_matrix_3x4fv *glUniformMatrix3x4fv;
static gl_uniform_matrix_4x3fv *glUniformMatrix4x3fv;
static gl_delete_program *glDeleteProgram;
static gl_gen_buffers *glGenBuffers;
static gl_bind_buffer *glBindBuffer;
static gl_buffer_data *glBufferData;
static gl_enable_vertex_attrib_array *glEnableVertexAttribArray;
static gl_disable_vertex_attrib_array *glDisableVertexAttribArray;
static gl_delete_buffers *glDeleteBuffers;
static gl_unmap_buffer *glUnmapBuffer;
static gl_get_program_info_log *glGetProgramInfoLog;
static gl_vertex_attrib_pointer *glVertexAttribPointer;
static gl_get_attrib_location *glGetAttribLocation;

// OpenGL 3
static gl_gen_vertex_arrays *glGenVertexArrays;
static gl_bind_vertex_array *glBindVertexArray;
static gl_delete_vertex_arrays *glDeleteVertexArrays;
static gl_map_buffer_range *glMapBufferRange;
static gl_clear_buffer_fv* glClearBufferfv;

// OpenGL 4.2
static gl_tex_storage_2d *glTexStorage2D;

// OpenGL 4.3
static gl_bind_vertex_buffer *glBindVertexBuffer;
static gl_vertex_attrib_format *glVertexAttribFormat;
static gl_vertex_attrib_binding *glVertexAttribBinding;

// OpenGL 4.5
static gl_create_vertex_arrays* glCreateVertexArrays;
static gl_named_buffer_storage* glNamedBufferStorage;
static gl_enable_vertex_array_attrib* glEnableVertexArrayAttrib;
static gl_disable_vertex_array_attrib* glDisableVertexArrayAttrib;
static gl_vertex_array_vertex_buffer* glVertexArrayVertexBuffer;
static gl_vertex_array_attrib_binding* glVertexArrayAttribBinding;
static gl_vertex_array_attrib_ib_format* glVertexArrayAttribFormat;
static gl_create_buffers* glCreateBuffers;
static gl_create_textures* glCreateTextures;
static gl_texture_storage_2d* glTextureStorage2D;
static gl_texture_sub_image_2d* glTextureSubImage2D;

void
Render_Initialize()
{
	glEnable(GL_DEPTH_TEST);

	// OpenGL 2
	glCreateShader = (gl_create_shader *)wglGetProcAddress("glCreateShader");
	glShaderSource = (gl_shader_source *)wglGetProcAddress("glShaderSource");
	glCompileShader = (gl_compile_shader *)wglGetProcAddress("glCompileShader");
	glGetShaderiv = (gl_get_shader_iv *)wglGetProcAddress("glGetShaderiv");
	glCreateProgram = (gl_create_program *)wglGetProcAddress("glCreateProgram");
	glAttachShader = (gl_attach_shader *)wglGetProcAddress("glAttachShader");
	glLinkProgram = (gl_link_program *)wglGetProcAddress("glLinkProgram");
	glDetachShader = (gl_detach_shader *)wglGetProcAddress("glDetachShader");
	glDeleteShader = (gl_delete_shader *)wglGetProcAddress("glDeleteShader");
	glGetShaderInfoLog = (gl_get_shader_info_log *)wglGetProcAddress("glGetShaderInfoLog");
	glGetProgramiv = (gl_get_program_iv *)wglGetProcAddress("glGetProgramiv");
	glUseProgram = (gl_use_program *)wglGetProcAddress("glUseProgram");
	glGetUniformLocation = (gl_get_uniform_location *)wglGetProcAddress("glGetUniformLocation");
	glDeleteProgram = (gl_delete_program *)wglGetProcAddress("glDeleteProgram");
	glUniform1i = (gl_uniform_1i *)wglGetProcAddress("glUniform1i");
	glUniform2i = (gl_uniform_2i *)wglGetProcAddress("glUniform2i");
	glUniform3i = (gl_uniform_3i *)wglGetProcAddress("glUniform3i");
	glUniform4i = (gl_uniform_4i *)wglGetProcAddress("glUniform4i");
	glUniform1iv = (gl_uniform_1iv *)wglGetProcAddress("glUniform1iv");
	glUniform2iv = (gl_uniform_2iv *)wglGetProcAddress("glUniform2iv");
	glUniform3iv = (gl_uniform_3iv *)wglGetProcAddress("glUniform3iv");
	glUniform4iv = (gl_uniform_4iv *)wglGetProcAddress("glUniform4iv");
	glUniform1ui = (gl_uniform_1ui *)wglGetProcAddress("glUniform1ui");
	glUniform2ui = (gl_uniform_2ui *)wglGetProcAddress("glUniform2ui");
	glUniform3ui = (gl_uniform_3ui *)wglGetProcAddress("glUniform3ui");
	glUniform4ui = (gl_uniform_4ui *)wglGetProcAddress("glUniform4ui");
	glUniform1uiv = (gl_uniform_1uiv *)wglGetProcAddress("glUniform1uiv");
	glUniform2uiv = (gl_uniform_2uiv *)wglGetProcAddress("glUniform2uiv");
	glUniform3uiv = (gl_uniform_3uiv *)wglGetProcAddress("glUniform3uiv");
	glUniform4uiv = (gl_uniform_4uiv *)wglGetProcAddress("glUniform4uiv");
	glUniform1f = (gl_uniform_1f *)wglGetProcAddress("glUniform1f");
	glUniform2f = (gl_uniform_2f *)wglGetProcAddress("glUniform2f");
	glUniform3f = (gl_uniform_3f *)wglGetProcAddress("glUniform3f");
	glUniform4f = (gl_uniform_4f *)wglGetProcAddress("glUniform4f");
	glUniform1fv = (gl_uniform_1fv *)wglGetProcAddress("glUniform1fv");
	glUniform2fv = (gl_uniform_2fv *)wglGetProcAddress("glUniform2fv");
	glUniform3fv = (gl_uniform_3fv *)wglGetProcAddress("glUniform3fv");
	glUniform4fv = (gl_uniform_4fv *)wglGetProcAddress("glUniform4fv");
	glUniformMatrix2fv = (gl_uniform_matrix_2fv *)wglGetProcAddress("glUniformMatrix2fv");
	glUniformMatrix3fv = (gl_uniform_matrix_3fv *)wglGetProcAddress("glUniformMatrix3fv");
	glUniformMatrix4fv = (gl_uniform_matrix_4fv *)wglGetProcAddress("glUniformMatrix4fv");
	glUniformMatrix2x3fv = (gl_uniform_matrix_2x3fv *)wglGetProcAddress("glUniformMatrix2x3fv");
	glUniformMatrix3x2fv = (gl_uniform_matrix_3x2fv *)wglGetProcAddress("glUniformMatrix3x2fv");
	glUniformMatrix2x4fv = (gl_uniform_matrix_2x4fv *)wglGetProcAddress("glUniformMatrix2x4fv");
	glUniformMatrix4x2fv = (gl_uniform_matrix_4x2fv *)wglGetProcAddress("glUniformMatrix4x2fv");
	glUniformMatrix3x4fv = (gl_uniform_matrix_3x4fv *)wglGetProcAddress("glUniformMatrix3x4fv");
	glUniformMatrix4x3fv = (gl_uniform_matrix_4x3fv *)wglGetProcAddress("glUniformMatrix4x3fv");
	glGenBuffers = (gl_gen_buffers *)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (gl_bind_buffer *)wglGetProcAddress("glBindBuffer");
	glBufferData = (gl_buffer_data *)wglGetProcAddress("glBufferData");
	glEnableVertexAttribArray = (gl_enable_vertex_attrib_array *)wglGetProcAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (gl_disable_vertex_attrib_array *)wglGetProcAddress("glDisableVertexAttribArray");
	glDeleteBuffers = (gl_delete_buffers *)wglGetProcAddress("glDeleteBuffers");
	glUnmapBuffer = (gl_unmap_buffer*)wglGetProcAddress("glUnmapBuffer");
	glGetProgramInfoLog = (gl_get_program_info_log*)wglGetProcAddress("glGetProgramInfoLog");
	glVertexAttribPointer = (gl_vertex_attrib_pointer*)wglGetProcAddress("glVertexAttribPointer");
	glGetAttribLocation = (gl_get_attrib_location*)wglGetProcAddress("glGetAttribLocation");

	// OpenGL 3
	glGenVertexArrays = (gl_gen_vertex_arrays *)wglGetProcAddress("glGenVertexArrays");
	glBindVertexArray = (gl_bind_vertex_array *)wglGetProcAddress("glBindVertexArray");
	glDeleteVertexArrays = (gl_delete_vertex_arrays *)wglGetProcAddress("glDeleteVertexArrays");
	glMapBufferRange = (gl_map_buffer_range *)wglGetProcAddress("glMapBufferRange");
	glClearBufferfv = (gl_clear_buffer_fv *)wglGetProcAddress("glClearBufferfv");

	// OpenGL 4.2
	glTexStorage2D = (gl_tex_storage_2d *)wglGetProcAddress("glTexStorage2D");

	// OpenGL 4.3
	glBindVertexBuffer = (gl_bind_vertex_buffer *)wglGetProcAddress("glBindVertexBuffer");
	glVertexAttribFormat = (gl_vertex_attrib_format *)wglGetProcAddress("glVertexAttribFormat");
	glVertexAttribBinding = (gl_vertex_attrib_binding *)wglGetProcAddress("glVertexAttribBinding");

	// OpenGL 4.5
	glCreateVertexArrays = (gl_create_vertex_arrays *)wglGetProcAddress("glCreateVertexArrays");
	glNamedBufferStorage = (gl_named_buffer_storage *)wglGetProcAddress("glNamedBufferStorage");
	glEnableVertexArrayAttrib = (gl_enable_vertex_array_attrib *)wglGetProcAddress("glEnableVertexArrayAttrib");
	glDisableVertexArrayAttrib = (gl_disable_vertex_array_attrib *)wglGetProcAddress("glDisableVertexArrayAttrib");
	glVertexArrayVertexBuffer = (gl_vertex_array_vertex_buffer *)wglGetProcAddress("glVertexArrayVertexBuffer");
	glVertexArrayAttribBinding = (gl_vertex_array_attrib_binding *)wglGetProcAddress("glVertexArrayAttribBinding");
	glVertexArrayAttribFormat = (gl_vertex_array_attrib_ib_format *)wglGetProcAddress("glVertexArrayAttribFormat");
	glCreateBuffers = (gl_create_buffers*)wglGetProcAddress("glCreateBuffers");
	glCreateTextures = (gl_create_textures *)wglGetProcAddress("glCreateTextures");
	glTextureStorage2D = (gl_texture_storage_2d *)wglGetProcAddress("glTextureStorage2D");
	glTextureSubImage2D = (gl_texture_sub_image_2d *)wglGetProcAddress("glTextureSubImage2D");
}

static uint32 ShaderProgram = 0;
static uint32 VertexBufferObject = 0;
static uint32 VertexArrayObject = 0;

void
Render_Practice()
{
	glViewport(0, 0, 1200, 800);

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