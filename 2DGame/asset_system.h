#ifndef ASSET_SYSTEM_H
#define ASSET_SYSTEM_H

#include "bmp.h"

struct Texture
{
	char* FileName;
	uint32 Width, Height;
	uint8* Data, BytesPerPixel;
};

Texture* Asset_LoadTexture(char* FileName);

#endif