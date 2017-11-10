#include "model_system.h"

static unsigned int IDCount = 0;

Model* Model_CreateRect()
{
	Model* NewRect = new Model;

	NewRect->ID = IDCount;
	IDCount++;
	NewRect->VerticeBufferID = 0;
	NewRect->TextCoordBufferID = 0;
	NewRect->VAOID = 0;

	NewRect->VerticeData = new float[18]{};
	NewRect->VerticeData[3] = 1.0f;
	NewRect->VerticeData[6] = 1.0f;
	NewRect->VerticeData[7] = 1.0f;
	NewRect->VerticeData[9] = 1.0f;
	NewRect->VerticeData[10] = 1.0f;
	NewRect->VerticeData[13] = 1.0f;

	NewRect->VerticeByteSize = 18 * sizeof(float);

	NewRect->TextCoordData = new float[12]{};
	NewRect->TextCoordData[2] = 1.0f; 
	NewRect->TextCoordData[4] = 1.0f;
	NewRect->TextCoordData[5] = 1.0f;
	NewRect->TextCoordData[6] = 1.0f;
	NewRect->TextCoordData[7] = 1.0f;
	NewRect->TextCoordData[9] = 1.0f;

	NewRect->TextCoordByteSize = 12 * sizeof(float);

	return NewRect;
}