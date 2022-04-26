#pragma once

#include "Mesh.h"

using namespace std;

class ShapeBuilder
{
public:
	static void UBuildPyramid(GLMesh& mesh, const vector<float>& p, float height);
	static void UBuildCylinder(GLMesh& mesh, vector<float> properties, float radius, float length);
	static void UBuildCone(GLMesh& mesh, const vector<float>& p, float r, float l, float s);
	static void UBuildPlane(GLMesh& mesh, vector<float> properties);
	static void UTranslator(GLMesh& mesh, const vector<float>& p);
};

