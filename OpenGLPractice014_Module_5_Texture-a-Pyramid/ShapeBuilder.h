#pragma once

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>


// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <camera.h>

using namespace std;

struct GLMesh
{
	//vertex array
	GLuint vao;
	//vertex buffer
	GLuint vbos[2];
	//indices of the mesh
	GLuint nIndices;



	glm::mat4 scale;
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::mat4 model;



};

class ShapeBuilder
{

public:
	void UBuildPyramid(GLMesh& mesh, vector<float> properties);
	void UBuildCylinder(GLMesh& mesh, vector<float> properties, float radius, float length);
	void UBuildCone(GLMesh& mesh, vector<float> properties, float radius, float length);
	void UBuildPlane(GLMesh& mesh, vector<float> properties);
};

