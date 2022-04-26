#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "ShapeBuilder.h"

using namespace std;


void ShapeBuilder::UBuildPyramid(GLMesh& mesh, const vector<float>& p /*properties*/, float h /*height*/)
{
	GLfloat verts[] =
	{
		// Vertex Positions    // Texture coords
		 0.0f,	h,		0.0f,	0.5f, 1.0f,		//back side
		-1.0f, -0.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -0.0f, -1.0f,	1.0f, 0.0f,

		 0.0f,  h,		0.0f,	0.5f, 1.0f,		//left side
		-1.0f, -0.0f, -1.0f,	0.0f, 0.0f,
		-1.0f, -0.0f,  1.0f,	1.0f, 0.0f,

		 0.0f,  h,		0.0f,	0.5f, 1.0f,		//front
		-1.0f, -0.0f,  1.0f,	0.0f, 0.0f,
		 1.0f, -0.0f,  1.0f,	1.0f, 0.0f,

		 0.0f,  h,		0.0f,	0.5f, 1.0f,		//right side
		 1.0f, -0.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -0.0f,  1.0f,	1.0f, 0.0f,

		-1.0f, -0.0f, -1.0f,	1.0f, 0.0f,		//bottom back
		 1.0f, -0.0f, -1.0f,	1.0f, 1.0f,
		-1.0f, -0.0f,  1.0f,	0.0f, 0.0f,

		 1.0f, -0.0f, -1.0f,	1.0f, 1.0f,		//bottom front
		-1.0f, -0.0f,  1.0f,	0.0f, 0.0f,
		 1.0f, -0.0f,  1.0f,	0.0f, 1.0f,
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


	UTranslator(mesh, p);

}

void ShapeBuilder::UBuildCone(GLMesh& mesh, const vector<float>& p /*properties*/, 
	float r /*radius*/, float l /*length*/, float s = 12.0f)
{
	const float PI = 3.14f;

	//const float STEP = 12;
	float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (int i = 1; i < s + 1; i++) {

		// triangle top, fan
		// point 1
		v.push_back(0.0f); v.push_back(0.0f); v.push_back(0.0f);    // center coords
		v.push_back(0.5f); v.push_back(0.0f);   // text

		// point 2
		v.push_back(r * cos(i * sectorStep));    // x
		v.push_back(r * sin(i * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(0.0f);   // text

		//point 3
		v.push_back(r * cos((i + 1) * sectorStep));    // x
		v.push_back(r * sin((i + 1) * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(1.0f);   // text


		// side triangle
		// point 1
		v.push_back(r * cos((i + 1) * sectorStep));    // x
		v.push_back(r * sin((i + 1) * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(0.0f); v.push_back(0.0f);   // text

		// point 2, point of cone
		v.push_back(0.0f); v.push_back(0.0f); v.push_back(l);    // center coords
		v.push_back(0.5f); v.push_back(1.0f);   // text

		// point 3
		v.push_back(r * cos(i * sectorStep));    // x
		v.push_back(r * sin(i * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(0.0f);   // text

		
	}

	GLfloat verts[740];

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

	UTranslator(mesh, p);

	
}


void ShapeBuilder::UTranslator(GLMesh& mesh, const vector<float>& p)
{
	// scale the object
	mesh.scale = glm::scale(glm::vec3(p[4], p[5], p[6]));

	const glm::mat4 rot = glm::mat4(1.0f);
	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.xrotation = glm::rotate(rot, glm::radians(p[7]), glm::vec3(p[8], p[9], p[10]));
	mesh.yrotation = glm::rotate(rot, glm::radians(p[11]), glm::vec3(p[12], p[13], p[14]));
	mesh.zrotation = glm::rotate(rot, glm::radians(p[15]), glm::vec3(p[16], p[17], p[18]));


	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(p[19], p[20], p[21]));

	mesh.model = mesh.translation * mesh.xrotation * mesh.zrotation * mesh.yrotation * mesh.scale;

	mesh.gUVScale = glm::vec2(p[22], p[23]);		// use this to scale the texture to be larger
}

