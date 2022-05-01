#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>

#include "ShapeBuilder.h"

using namespace std;





void ShapeBuilder::UBuildPyramid(GLMesh& mesh)
{
	float h = mesh.height;
	mesh.v = {
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
		 1.0f, -0.0f,  1.0f,	0.0f, 1.0f
	};
		
	UTranslator(mesh);

}

void ShapeBuilder::UBuildCone(GLMesh& mesh)
{
	float r = mesh.radius;
	float l = mesh.length;
	float s = mesh.number_of_sides;

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (auto i = 1; i < s + 1; i++) {

		// triangle fan, bottom
		v.insert(v.end(), {0.0f, 0.0f, 0.0f, 0.5f, 0.0f});		// center point
		v.insert(v.end(), { r * cos(i * sectorStep) , r * sin(i * sectorStep) , 0.0f , 1.0f , 0.0f });
		v.insert(v.end(), { r * cos((i + 1) * sectorStep) , r * sin((i + 1) * sectorStep) , 0.0f , 1.0f , 1.0f });

		// side triangle + point
		v.insert(v.end(), { r * cos((i + 1) * sectorStep) , r * sin((i + 1) * sectorStep) , 0.0f , 0.0f , 0.0f});
		v.insert(v.end(), {0.0f , 0.0f , l , 0.5f , 1.0f});
		v.insert(v.end(), { r * cos(i * sectorStep) , r * sin(i * sectorStep) , 0.0f , 1.0f , 0.0f});
		
	}

	mesh.v = v;
	v.clear();	// clear the local vector
	
	UTranslator(mesh);
}

void ShapeBuilder::UBuildCylinder(GLMesh& mesh)
{
	float r = mesh.radius;
	float l = mesh.length;
	float s = mesh.number_of_sides;
	float h = mesh.height;

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (auto i = 1; i < s + 1; i++)
	{
		// triangle fan, bottom
		v.insert(v.end(), { 0.5f, 0.5f, 0.0f, 0.5f, 0.5f });		// center point
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) , 0.5f + r * sin(i * sectorStep) , 0.0f , 0.5f + (r * cos((i)*sectorStep)) , 0.5f + (r * sin((i)*sectorStep))  });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) , 0.5f + r * sin((i + 1) * sectorStep) , 0.0f , 0.5f + (r * cos((i + 1) * sectorStep)) , 0.5f + (r * sin((i + 1) * sectorStep))  });
		std::cout << 0.5f +  r * cos(i * sectorStep) << ", " << 0.5f + r * sin(i * sectorStep) << endl;
	}

	for (auto i = 1; i < s + 1; i++)
	{
		// triangle fan, bottom
		v.insert(v.end(), { 0.5f, 0.5f, l, 0.5f, 0.5f });		// center point
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) , 0.5f + r * sin(i * sectorStep) , l , 0.5f + (r * cos((i)*sectorStep)) , 0.5f + (r * sin((i)*sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) , 0.5f + r * sin((i + 1) * sectorStep) , l , 0.5f + (r * cos((i + 1) * sectorStep)) , 0.5f + (r * sin((i + 1) * sectorStep)) });
		std::cout << 0.5f + r * cos(i * sectorStep) << ", " << 0.5f + r * sin(i * sectorStep) << endl;
	}

	for (auto i = 1; i < s + 1; i++)
	{
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) , 0.5f + r * sin(i * sectorStep) , 0.0f , 0.5f + (r * cos((i)*sectorStep)) , 0.5f + (r * sin((i)*sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) , 0.5f + r * sin(i * sectorStep) , l , 0.5f + (r * cos((i)*sectorStep)) , 0.5f + (r * sin((i)*sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) , 0.5f + r * sin((i + 1) * sectorStep) , l , 0.5f + (r * cos((i + 1) * sectorStep)) , 0.5f + (r * sin((i + 1) * sectorStep)) });

		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) , 0.5f + r * sin((i + 1) * sectorStep) , l , 0.5f + (r * cos((i + 1) * sectorStep)) , 0.5f + (r * sin((i + 1) * sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) , 0.5f + r * sin((i + 1) * sectorStep) , 0.0f , 0.5f + (r * cos((i + 1) * sectorStep)) , 0.5f + (r * sin((i + 1) * sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) , 0.5f + r * sin(i * sectorStep) , 0.0f , 0.5f + (r * cos((i)*sectorStep)) , 0.5f + (r * sin((i)*sectorStep)) });


	}
	

	mesh.v = v;
	v.clear();




	UTranslator(mesh);
	
}


void ShapeBuilder::UBuildTriangles(GLMesh& mesh)
{
	mesh.v = {
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 0
		-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	// 1
		 0.0f, 0.0f, 0.0f, 0.5f, 0.0f,	// 2

		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 0
		 0.0f, 0.0f, 0.0f, 0.5f, 0.0f,	// 2
		 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,	// 3

		 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,	// 3
		 0.0f, 0.0f, 0.0f, 0.5f, 0.0f,	// 2
		 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	// 5

		 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,	// 3
		 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	// 5
		 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	// 4

	};
	
	UTranslator(mesh);
	
}


void ShapeBuilder::UTranslator(GLMesh& mesh)
{
	constexpr GLuint floatsPerVertex = 3;
	constexpr GLuint floatsPerColor = 0;
	constexpr GLuint floatsPerUV = 2;

	mesh.nIndices = mesh.v.size() / (floatsPerVertex + floatsPerUV + floatsPerColor);

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	// Create VBO
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer

	glBufferData(
		GL_ARRAY_BUFFER,
		mesh.v.size() * sizeof(float),
		&mesh.v.front(),
		GL_STATIC_DRAW
	); // Sends vertex or coordinate data to the GPU

	// Strides between vertex coordinates
	constexpr GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV);

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(2);
	

	// scale the object
	mesh.scale = glm::scale(glm::vec3(mesh.p[4], mesh.p[5], mesh.p[6]));

	const glm::mat4 rot = glm::mat4(1.0f);
	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.xrotation = glm::rotate(rot, glm::radians(mesh.p[7]), glm::vec3(mesh.p[8], mesh.p[9], mesh.p[10]));
	mesh.yrotation = glm::rotate(rot, glm::radians(mesh.p[11]), glm::vec3(mesh.p[12], mesh.p[13], mesh.p[14]));
	mesh.zrotation = glm::rotate(rot, glm::radians(mesh.p[15]), glm::vec3(mesh.p[16], mesh.p[17], mesh.p[18]));


	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(mesh.p[19], mesh.p[20], mesh.p[21]));

	mesh.model = mesh.translation * mesh.xrotation * mesh.zrotation * mesh.yrotation * mesh.scale;

	mesh.gUVScale = glm::vec2(mesh.p[22], mesh.p[23]);		// use this to scale the texture to be larger
}

