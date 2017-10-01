#ifndef RENDER_LAYER_H
#define RENDER_LAYER_H

// NOTE: Warning! DO NOT put opengl.h before platform_layer.h
// doing so will result in errors. Windows.h must be called before OpenGL libraries

#include "platform_layer.h"
#include "opengl.h"
#include "shaders.h"

void
Render_Initialize();

void
Render_Practice();
void
Render_PracticeDraw();
void
Render_PracticeCleanup();

#endif
