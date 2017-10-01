#ifndef SHADERS_H
#define SHADERS_H

// NOTE: Temporary solution for shader storage.

static const char* VertexShaderString =
{
	"#version 450 core												\n"
	"																\n"
	"layout (location = 0) in vec3 PositionData;					\n"
	"																\n"
	"void main(void)												\n"
	"{																\n"
	"	gl_Position = vec4(PositionData, 1.0);						\n"
	"}																\n"
};

static const char* FragmentShaderString =
{
	"#version 450 core												\n"
	"																\n"
	"out vec4 FragColor;											\n"					
	"void main(void)												\n"
	"{																\n"
	"	FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);					\n"
	"}																\n"
};


#endif