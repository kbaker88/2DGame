#include "bmp.h"

#define WINDOWS_TYPE 16973 // 0x42 0x4D

void
BMP_ExtractImageData(uint8* DataInput, uint8** DataOutput,
	uint32* ImgWidth, uint32* ImgHeight, uint8* BytesPerPixel)
{
	uint16 HeaderType = (DataInput[1]) | (DataInput[0] << 8);
	uint32 BmpFileSize = (DataInput[2]) | (DataInput[3] << 8) |
		(DataInput[4] << 16) | (DataInput[5] << 24); 

	uint32 PixelArrayOffset = (DataInput[10]) | (DataInput[11] << 8) |
		(DataInput[12] << 16) | (DataInput[13] << 24);

	if (HeaderType == WINDOWS_TYPE)
	{
		uint32 HeaderSize = (DataInput[14]) | (DataInput[15] << 8) |
			(DataInput[16] << 16) | (DataInput[17] << 24);

		*ImgWidth = (DataInput[18]) | (DataInput[19] << 8) |
			(DataInput[20] << 16) | (DataInput[21] << 24);

		*ImgHeight = (DataInput[22]) | (DataInput[23] << 8) |
			(DataInput[24] << 16) | (DataInput[25] << 24);

		uint32 ImageArea = *ImgWidth * *ImgHeight;

		uint16 BitsPerPixel = (DataInput[28]) | (DataInput[29] << 8);
		*BytesPerPixel = BitsPerPixel / 8;

		uint32 CompressionMethod = (DataInput[30]) | (DataInput[31] << 8) |
			(DataInput[32] << 16) | (DataInput[33] << 24);
		
		uint32 ImageSize = (DataInput[34]) | (DataInput[35] << 8) |
			(DataInput[36] << 16) | (DataInput[37] << 24);

		if (ImageSize == 0)
		{
			ImageSize = ImageArea * *BytesPerPixel;
		}

		uint32 HorizontalRez = (DataInput[38]) | (DataInput[39] << 8) |
			(DataInput[40] << 16) | (DataInput[41] << 24);

		uint32 VerticalRez = (DataInput[42]) | (DataInput[43] << 8) |
			(DataInput[44] << 16) | (DataInput[45] << 24);

		uint32 NumberOfColorsInPalette = (DataInput[46]) | (DataInput[47] << 8) |
			(DataInput[48] << 16) | (DataInput[49] << 24);

		uint32 NumberOfImportantColors = (DataInput[50]) | (DataInput[51] << 8) |
			(DataInput[52] << 16) | (DataInput[53] << 24);

		uint32 BytesPerRow = ( (BitsPerPixel * *ImgWidth + 31) / 32 ) * 4;

		if ((CompressionMethod == 0) &&
			(NumberOfColorsInPalette == 0))
		{

			uint8* ImageData = new uint8[ImageSize]{};

			uint32 ImgDataIndex = 0;
			uint32 PaddingOffset = BytesPerRow - (*ImgWidth * *BytesPerPixel);
			for (uint32 HeightIndex = 0;
				HeightIndex < *ImgHeight;
				HeightIndex++)
			{
				for (uint32 RowIndex = 0;
					RowIndex < BytesPerRow;
					RowIndex += *BytesPerPixel)
				{
					ImageData[ImgDataIndex + 0] = DataInput[(HeightIndex * BytesPerRow) + RowIndex + PixelArrayOffset + 2];
					ImageData[ImgDataIndex + 1] = DataInput[(HeightIndex * BytesPerRow) + RowIndex + PixelArrayOffset + 1];
					ImageData[ImgDataIndex + 2] = DataInput[(HeightIndex * BytesPerRow) + RowIndex + PixelArrayOffset + 0];
					ImgDataIndex += *BytesPerPixel;
				}
				PixelArrayOffset += PaddingOffset;
			}

			*DataOutput = ImageData;
		}
		else
		{
			// ERROR FOR NOW
		}
	}
}