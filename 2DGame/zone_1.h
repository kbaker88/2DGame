#ifndef ZONE_1_H
#define ZONE_1_H

#include "render_layer.h"
#include "camera_system.h"

void 
Zone_1_Load();
void 
Zone_1_Run();
int32
Zone_1_Status();
void 
Zone_1_Cleanup();
int64
Zone_1_MsgHandle(void* Window, uint32 Message,
	uint64 wParam, int64 lParam);

#endif