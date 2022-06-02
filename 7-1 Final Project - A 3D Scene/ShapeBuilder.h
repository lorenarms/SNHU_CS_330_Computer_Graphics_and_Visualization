#pragma once

#include "Mesh.h"

using namespace std;

class ShapeBuilder
{
public:
	static void UBuildPyramid(GLMesh& mesh);

	static void UBuildCube(GLMesh& mesh);

	static void UBuildCone(GLMesh& mesh);

	static void UBuildCylinder(GLMesh& mesh);
	static void UBuildHollowCylinder(GLMesh& mesh);

	static void UBuildPlane(GLMesh& mesh);

	static void UBuildCircle(GLMesh& mesh);

	static void UBuildPotBottom(GLMesh& mesh);
	static void UBuildLeaves(GLMesh& mesh);

	static void UTranslator(GLMesh& mesh);

};

