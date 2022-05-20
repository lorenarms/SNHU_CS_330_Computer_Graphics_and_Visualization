#pragma once
#include "ShapeData.h"
typedef unsigned int uint;

class ShapeGenerator
{
	static ShapeData makePlaneVerts(uint dimensions);
	static ShapeData makePlaneIndices(uint dimensions);

	
public:

	static ShapeData makePlane(uint dimensions = 10);
	static ShapeData makeSphere(uint tesselation = 20);
	
};
