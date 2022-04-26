#pragma once

#include "Mesh.h"

using namespace std;

class ShapeBuilder
{
public:
	static void UBuildPyramid(GLMesh& mesh, const vector<float>& properties);
	static void UBuildCylinder(GLMesh& mesh, vector<float> properties, float radius, float length);
	static void UBuildCone(GLMesh& mesh, const vector<float>& properties, float radius, float length);
	static void UBuildPlane(GLMesh& mesh, vector<float> properties);
};

