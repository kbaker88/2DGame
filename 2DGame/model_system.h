#ifndef MODEL_SYSTEM_H
#define MODEL_SYSTEM_H

struct Model
{
	float *VerticeData, *TextCoordData;
	unsigned int ID, VerticeBufferID, TextCoordBufferID, 
		VAOID, VerticeByteSize, TextCoordByteSize;
};

Model* Model_CreateRect();

#endif
