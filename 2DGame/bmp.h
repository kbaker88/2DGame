#ifndef BMP_H
#define BMP_H

#include "platform_layer.h"

void
BMP_ExtractImageData(unsigned char* DataInput, unsigned char* DataOutput,
	uint32* ImgWidth, uint32* ImgHeight);

#endif
