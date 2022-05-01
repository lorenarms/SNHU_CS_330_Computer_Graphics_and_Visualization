#pragma once

#include "Mesh.h"

using namespace std;

class ShapeBuilder
{
public:
	static void UBuildPyramid(GLMesh& mesh);
	static void UBuildCone(GLMesh& mesh);
	static void UBuildTriangles(GLMesh& mesh);
	static void UBuildCylinder(GLMesh& mesh);

	static void UBuildPlane(GLMesh& mesh, vector<float> properties);
	static void UTranslator(GLMesh& mesh);

};

