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
	//indices of the mesh
	GLuint nIndices;

	// each shape gets a matrix object
	glm::mat4 scale;
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::mat4 model;
	glm::vec2 gUVScale;

	GLuint textureId;

	GLint gTextWrapMode = GL_REPEAT;
	//texture wrapping mode: repeat texture

	//also can use:
	//GLint gTextWrapMode = GL_MIRRORED_REPEAT;
	//GLint gTextWrapMode = GL_CLAMP_TO_EDGE;
	//GLint gTextWrapMode = GL_CLAMP_TO_BORDER;

};