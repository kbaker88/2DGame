#include "render_layer.h"

// OpenGL 2
gl_create_shader *glCreateShader;
gl_shader_source *glShaderSource;
gl_compile_shader *glCompileShader;
gl_get_shader_iv *glGetShaderiv;
gl_create_program *glCreateProgram;
gl_attach_shader *glAttachShader;
gl_link_program *glLinkProgram;
gl_detach_shader *glDetachShader;
gl_delete_shader *glDeleteShader;
gl_get_shader_info_log *glGetShaderInfoLog;
gl_get_program_iv *glGetProgramiv;
gl_use_program *glUseProgram;
gl_get_uniform_location *glGetUniformLocation;
gl_uniform_1i *glUniform1i;
gl_uniform_2i *glUniform2i;
gl_uniform_3i *glUniform3i;
gl_uniform_4i *glUniform4i;
gl_uniform_1iv *glUniform1iv;
gl_uniform_2iv *glUniform2iv;
gl_uniform_3iv *glUniform3iv;
gl_uniform_4iv *glUniform4iv;
gl_uniform_1ui *glUniform1ui;
gl_uniform_2ui *glUniform2ui;
gl_uniform_3ui *glUniform3ui;
gl_uniform_4ui *glUniform4ui;
gl_uniform_1uiv *glUniform1uiv;
gl_uniform_2uiv *glUniform2uiv;
gl_uniform_3uiv *glUniform3uiv;
gl_uniform_4uiv *glUniform4uiv;
gl_uniform_1f *glUniform1f;
gl_uniform_2f *glUniform2f;
gl_uniform_3f *glUniform3f;
gl_uniform_4f *glUniform4f;
gl_uniform_1fv *glUniform1fv;
gl_uniform_2fv *glUniform2fv;
gl_uniform_3fv *glUniform3fv;
gl_uniform_4fv *glUniform4fv;
gl_uniform_matrix_2fv *glUniformMatrix2fv;
gl_uniform_matrix_3fv *glUniformMatrix3fv;
gl_uniform_matrix_4fv *glUniformMatrix4fv;
gl_uniform_matrix_2x3fv *glUniformMatrix2x3fv;
gl_uniform_matrix_3x2fv *glUniformMatrix3x2fv;
gl_uniform_matrix_2x4fv *glUniformMatrix2x4fv;
gl_uniform_matrix_4x2fv *glUniformMatrix4x2fv;
gl_uniform_matrix_3x4fv *glUniformMatrix3x4fv;
gl_uniform_matrix_4x3fv *glUniformMatrix4x3fv;
gl_delete_program *glDeleteProgram;
gl_gen_buffers *glGenBuffers;
gl_bind_buffer *glBindBuffer;
gl_buffer_data *glBufferData;
gl_enable_vertex_attrib_array *glEnableVertexAttribArray;
gl_disable_vertex_attrib_array *glDisableVertexAttribArray;
gl_delete_buffers *glDeleteBuffers;
gl_unmap_buffer *glUnmapBuffer;
gl_get_program_info_log *glGetProgramInfoLog;
gl_vertex_attrib_pointer *glVertexAttribPointer;
gl_get_attrib_location *glGetAttribLocation;

// OpenGL 3
gl_gen_vertex_arrays *glGenVertexArrays;
gl_bind_vertex_array *glBindVertexArray;
gl_delete_vertex_arrays *glDeleteVertexArrays;
gl_map_buffer_range *glMapBufferRange;
gl_clear_buffer_fv* glClearBufferfv;

// OpenGL 4.2
gl_tex_storage_2d *glTexStorage2D;

// OpenGL 4.3
gl_bind_vertex_buffer *glBindVertexBuffer;
gl_vertex_attrib_format *glVertexAttribFormat;
gl_vertex_attrib_binding *glVertexAttribBinding;

// OpenGL 4.5
gl_create_vertex_arrays* glCreateVertexArrays;
gl_named_buffer_storage* glNamedBufferStorage;
gl_enable_vertex_array_attrib* glEnableVertexArrayAttrib;
gl_disable_vertex_array_attrib* glDisableVertexArrayAttrib;
gl_vertex_array_vertex_buffer* glVertexArrayVertexBuffer;
gl_vertex_array_attrib_binding* glVertexArrayAttribBinding;
gl_vertex_array_attrib_ib_format* glVertexArrayAttribFormat;
gl_create_buffers* glCreateBuffers;
gl_create_textures* glCreateTextures;
gl_texture_storage_2d* glTextureStorage2D;
gl_texture_sub_image_2d* glTextureSubImage2D;

void
OpenGL_LoadFunctions()
{
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