#ifndef BMP_H
#define BMP_H

#include "platform_layer.h"

void
BMP_ExtractImageData(uint8* DataInput, uint8** DataOutput,
	uint32* ImgWidth, uint32* ImgHeight, uint8* BytesPerPixel);

#endif
