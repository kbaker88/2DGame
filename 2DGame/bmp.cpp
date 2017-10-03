#include "bmp.h"

#define WINDOWS_TYPE 40

void
BMP_ExtractImageData(unsigned char* DataInput, unsigned char* DataOutput,
	uint32* ImgWidth, uint32* ImgHeight)
{
	uint32 HeaderSize = (DataInput[14]) | (DataInput[15] << 8) |
		(DataInput[16] << 16) | (DataInput[17] << 24);

	if (HeaderSize == WINDOWS_TYPE) 
	{
		*ImgWidth = (DataInput[18]) | (DataInput[19] << 8) |
			(DataInput[20] << 16) | (DataInput[21] << 24);

		*ImgHeight = (DataInput[22]) | (DataInput[23] << 8) |
			(DataInput[24] << 16) | (DataInput[25] << 24);

		uint32 ImageArea = *ImgWidth * *ImgHeight;

		uint16 BitsPerPixel = (DataInput[28]) | (DataInput[29] << 8);
		uint8 BytesPerPixel = BitsPerPixel / 8;

		DataOutput = new uint8[ImageArea * BytesPerPixel];

		for (uint32 Index = 0;
			Index < ImageArea;
			Index += 3)
		{
			DataInput[Index + 0] = DataInput[Index + 56];
			DataInput[Index + 1] = DataInput[Index + 55];
			DataInput[Index + 2] = DataInput[Index + 54];
		}

		int x = 0;
	}
}