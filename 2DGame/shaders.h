#ifndef SHADERS_H
#define SHADERS_H

// NOTE: Temporary solution for shader storage.

static const char* VertexShaderString =
{
	"#version 450 core												\n"
	"																\n"
	"layout (location = 0) in vec3 PositionData;					\n"
	"layout (location = 1) in vec2 TextureCoord;					\n"
	"																\n"
	"out vec2 TexCoord;												\n"
	"																\n"
	"void main(void)												\n"
	"{																\n"
	"	TexCoord = TextureCoord;									\n"
	"	gl_Position = vec4(PositionData, 1.0);						\n"
	"}																\n\0"
};

static const char* FragmentShaderString =
{
	"#version 450 core												\n"
	"																\n"
	"in vec2 TexCoord;												\n"
	"																\n"
	"uniform sampler2D TextureData;									\n"
	"																\n"
	"out vec4 FragColor;											\n"
	"																\n"
	"void main(void)												\n"
	"{																\n"
	//"	FragColor = vec4(0.0f, 1.0f, 0.0f, 0.5f);					\n"
	"	FragColor = texture(TextureData, TexCoord);					\n"
	"}																\n\0"
};


#endif