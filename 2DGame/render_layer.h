#ifndef RENDER_LAYER_H
#define RENDER_LAYER_H

// NOTE: Warning! DO NOT put opengl.h before platform_layer.h
// doing so will result in errors. Windows.h must be called before OpenGL libraries

#include "platform_layer.h"
#include "opengl.h"

void
Render_Initialize();

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

#endif
