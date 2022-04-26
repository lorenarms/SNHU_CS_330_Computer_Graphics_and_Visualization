#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "ShapeBuilder.h"

using namespace std;


void ShapeBuilder::UBuildPyramid(GLMesh& mesh, const vector<float>& properties)
{
	GLfloat verts[] =
	{
		// Vertex Positions    // Texture coords
		 0.0f,  0.7f,  0.0f,	0.5f, 1.0f,		//back side
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,	1.0f, 0.0f,

		 0.0f,  0.7f,  0.0f,	0.5f, 1.0f,		//left side
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,	1.0f, 0.0f,

		 0.0f,  0.7f,  0.0f,	0.5f, 1.0f,		//front
		-1.0f, -1.0f,  1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,	1.0f, 0.0f,

		 0.0f,  0.7f,  0.0f,	0.5f, 1.0f,		//right side
		 1.0f, -1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,	1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		//bottom back
		 1.0f, -1.0f, -1.0f,	1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,	0.0f, 0.0f,

		 1.0f, -1.0f, -1.0f,	1.0f, 1.0f,		//bottom front
		-1.0f, -1.0f,  1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,	0.0f, 1.0f,
	};

	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerUV = 2;

	mesh.nIndices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerUV));

	glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(mesh.vao);

	// Create VBO
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	// Strides between vertex coordinates
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV);

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(2);


	// scale the object
	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale; \

	mesh.gUVScale = glm::vec2(3.0f, 3.0f);		// use this to scale the texture to be larger
}

void ShapeBuilder::UBuildCone(GLMesh& mesh, const vector<float>& properties, float radius, float length)
{
	const float PI = 3.14f;
	const float STEP = 12;
	float sectorStep = 2.0f * PI / STEP;

	vector<float> v;

	for (int i = 1; i < STEP; i++) {

		// triangle top, fan
		// point 1
		v.push_back(0.0f); v.push_back(0.0f); v.push_back(0.0f);    // center coords
		v.push_back(0.0f); v.push_back(0.0f);   // text

		// point 2
		v.push_back(radius * cos(i * sectorStep));    // x
		v.push_back(radius * sin(i * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(0.0f);   // text

		//point 3
		v.push_back(radius * cos((i + 1) * sectorStep));    // x
		v.push_back(radius * sin((i + 1) * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(1.0f);   // text


		// side triangle
		// point 1
		v.push_back(radius * cos((i + 1) * sectorStep));    // x
		v.push_back(radius * sin((i + 1) * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(1.0f);   // text

		// point 2, point of cone
		v.push_back(0.0f); v.push_back(0.0f); v.push_back(length);    // center coords
		v.push_back(0.0f); v.push_back(0.0f);   // text

		// point 3
		v.push_back(radius * cos(i * sectorStep));    // x
		v.push_back(radius * sin(i * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(0.0f);   // text

		// ADD IN LOGIC TO HAVE LAST TRIANGLE AND SIDE WRITTEN

	}

	GLfloat verts[370];

	for (int i = 0; i < v.size(); i++)
	{
		verts[i] = v[i];
	}

	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerUV = 2;

	mesh.nIndices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerUV));

	glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(mesh.vao);

	// Create VBO
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	// Strides between vertex coordinates
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV);

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(2);

	// scale the object
	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale;

	mesh.gUVScale = glm::vec2(1.0f, 1.0f);
}
