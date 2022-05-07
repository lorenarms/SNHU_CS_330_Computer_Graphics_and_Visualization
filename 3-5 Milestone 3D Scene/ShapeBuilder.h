#pragma once

#include "Mesh.h"

using namespace std;

class ShapeBuilder
{
public:
	static void UBuildPyramid(GLMesh& mesh);
	static void UBuildRainbowPyramid(GLMesh& mesh, float seed);
	static void UBuildCube(GLMesh& mesh);
	static void UBuildRainbowCube(GLMesh&, float seed);
	static void UBuildCone(GLMesh& mesh);
	static void UBuildTriangles(GLMesh& mesh);
	static void UBuildCylinder(GLMesh& mesh);
	static void UTranslator(GLMesh& mesh);
	static void UBuildCircle(GLMesh& mesh);

	static void UBuildPlane(GLMesh& mesh, vector<float> properties);

};

