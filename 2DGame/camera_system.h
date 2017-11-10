#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "math.h"

struct Camera
{
	m4 ViewMatrix, ProjectionMatrix;
	v3 Position, UpVector, ForwardVector;
};

void
Camera_SetPosition(Camera* CameraPtr, v3* NewPosition);

void
Camera_SetProjection(Camera* CameraPtr, float Width,
	float Height, v3* Position);

#endif
