#include "asset_system.h"

Texture* Asset_LoadTexture(char* FileName)
{
#if DEBUG_MODE
	if (!Platform_DoesFileExist(FileName))
	{
		Platform_ConsoleOutput("File Not Found.\n");
		return 0;
	}
#endif
	Texture* NewTexture = new Texture;
	NewTexture->FileName = FileName;
	uint8* BMPData = Platform_ReadFile(NewTexture->FileName);
	BMP_ExtractImageData(BMPData, &NewTexture->Data, &NewTexture->Width,
		&NewTexture->Height, &NewTexture->BytesPerPixel);

	if (BMPData)
	{
		delete[] BMPData;
	}

	return NewTexture;
}