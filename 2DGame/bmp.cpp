#include "bmp.h"

#define WINDOWS_TYPE 40

void
BMP_ExtractImageData(uint8* DataInput, uint8** DataOutput,
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

		uint32 ImageSize = ImageArea * BytesPerPixel;

		uint8* ImageData= new uint8[ImageSize]{};

		for (uint32 Index = 0;
			Index < ImageSize;
			Index += BytesPerPixel)
		{
			ImageData[Index + 0] = DataInput[Index + 56];
			ImageData[Index + 1] = DataInput[Index + 55];
			ImageData[Index + 2] = DataInput[Index + 54];
			ImageData[Index + 3] = DataInput[Index + 57];
		}

		*DataOutput = ImageData;
	}
}