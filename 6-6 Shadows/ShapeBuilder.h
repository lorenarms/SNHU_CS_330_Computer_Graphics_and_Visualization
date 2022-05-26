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
	static void UBuildRainbowCone(GLMesh& mesh, float seed);

	static void UBuildCylinder(GLMesh& mesh);
	static void UBuildRainbowCylinder(GLMesh& mesh, float seed);

	static void UBuildPlane(GLMesh& mesh);

	static void UBuildCircle(GLMesh& mesh);
	static void UBuildPlane(GLMesh& mesh, vector<float> properties);

	static void UTranslator(GLMesh& mesh);

};

