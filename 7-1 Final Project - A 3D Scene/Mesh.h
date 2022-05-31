#pragma once

// general includes
#include <iostream>
#include <vector>
#include <cstdlib>

// glew includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// camera
#include <camera.h>

struct GLMesh
{
	//vertex array
	GLuint vao;
	//vertex buffer
	GLuint vbo;
	//vertex buffer
	GLuint vbos[2];
	//indices of the mesh
	GLuint nIndices;

	//indices to draw
	std::vector<float> v;
	//translation properties of the shape
	std::vector<float> p;

	//physical properties of the shape
	float height;
	float length;
	float radius;
	float innerRadius;
	float number_of_sides;
	
	// each shape gets a matrix object
	glm::mat4 scale;
	glm::mat4 xrotation;
	glm::mat4 yrotation;
	glm::mat4 zrotation;
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::mat4 model;
	glm::vec2 gUVScale;

	// texture information
	const char* texFilename;
	GLuint textureId;

	//texture wrapping mode: repeat texture
	GLint gTextWrapMode = GL_REPEAT;
	//GLint gTextWrapMode = GL_MIRRORED_REPEAT;
	//GLint gTextWrapMode = GL_CLAMP_TO_EDGE;
	//GLint gTextWrapMode = GL_CLAMP_TO_BORDER;



	class Mesh
	{
	};
};