#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

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
		v.insert(v.end(), {0.0f, 0.0f, 0.0f, 0.5f, 0.0f});
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

	vector<float> p;

	// change "STEP" to increase / decrease resolution of cylinder
	constexpr float PI = 3.14f;
	float sectorStep = 2.0f * PI / s;

	// track which vertex is being added, add origin index when appropriate (every two)
	int step = 0;
	int vert = 2;


	// origin vertex of top and bottom of cylinder (center point)
	vector<float> v = {
								0.0f, 0.0f, 0.0f, p[0], p[1], p[2], p[3],	// top origin
								0.0f, 0.0f, l * -1, p[0], p[1], p[2], p[3]	// bottom origin
	};

	//vector<float> v = {
	//							0.0f, 0.0f, 0.0f, 0.5f, 0.0f,	// top origin
	//							0.0f, 0.0f, l * -1, 0.5f, 0.0f	// bottom origin
	//};

	// vectors for indices, sides of cylinder
	vector<int> index = { 0 };
	vector<int> sides;

	// build the top of the cylinder
	// used vectors so I could use "pushback" and have control over where points went
	for (int i = 0; i <= s * 2; ++i)
	{
		float sectorAngle = i * sectorStep;
		// vertex
		v.push_back(r * cos(sectorAngle)); // x
		v.push_back(r * sin(sectorAngle)); // y
		v.push_back(0.0f);						// z

		// color
		v.push_back(p[0]);
		v.push_back(p[1]);
		v.push_back(p[2]);
		v.push_back(p[3]);

		//v.insert(v.end(), { 0.0f , 1.0f , 0.0f });

		// track the vertices to draw, track the sides to draw
		index.push_back(vert);
		sides.push_back(vert + 1);

		// some maths to keep indices in proper order
		vert++;
		step++;

		// add in the origin index every two  vertices so that it connects them
		if (step == 2)
		{
			step = 0;
			vert--;
			index.push_back(0);

			// more maths to keep the indices in proper order
			sides.pop_back();
		}

	}

	// more maths to keep indices in proper order
	vert *= 2;
	step = 0;

	// set origin of bottom disk triangle fan
	index.push_back(1);

	// build bottom triangle fan of cylinder
	// same algorithm as above for top
	for (int i = 0; i <= s * 2; ++i)
	{
		float sectorAngle = i * sectorStep;
		v.push_back(r * cos(sectorAngle)); // x
		v.push_back(r * sin(sectorAngle)); // y
		v.push_back(l * -1);						// z

		// color
		v.push_back(p[0]);
		v.push_back(p[1]);
		v.push_back(p[2]);
		v.push_back(p[3]);
		//v.insert(v.end(), { 0.0f , 1.0f , 1.0f });
		index.push_back(vert);
		sides.push_back(vert - 1);

		// maths
		vert++;
		step++;
		if (step == 2)
		{
			step = 0;
			vert--;
			index.push_back(1);
			sides.pop_back();
		}
	}

	// remove the very last entry from the index array, tis' not needed
	index.pop_back();

	// list the indexes to draw the sides
	for (auto i = 0; i < sides.size() / 2 - 1; i++)
	{
		// lots of weird locations to find the given indices
		index.push_back(sides[i]);
		index.push_back(sides[i + 1]);
		index.push_back(sides[sides.size() / 2 + i]);

		index.push_back(sides[sides.size() / 2 + i]);
		index.push_back(sides[sides.size() / 2 + i + 1]);
		index.push_back(sides[i + 1]);


	}

	// okay all done! whew!
	// make an array of vertices
	// there doesn't seem to be an efficient way to convert from a vector to an array :(

	GLfloat verts[10000];
	for (int i = 0; i < v.size(); i++)
	{
		verts[i] = v[i];
	}

	// make an array for the indices
	GLushort indices[10000];
	for (int i = 0; i < index.size(); i++)
	{
		indices[i] = index[i];
	}

	mesh.v = v;
	v.clear();




	//struct each_pole {
	//	GLfloat x, z, y_start, y_end;
	//}; // struct


	//std::vector<each_pole> each_pole_vector; // vector of structs

	////Cylinder with y axis up
	//GLfloat cylinder_height = 1.0f,
	//	cylinder_radius = 0.5f,
	//	nr_of_points_cylinder = 360.f;

	//for (int i = 0; i < nr_of_points_cylinder; ++i)
	//{
	//	GLfloat u = i / (GLfloat)nr_of_points_cylinder;

	//	//Where the cylinder is in the x and z positions (3D space) 
	//	each_pole.x = center.x
	//		+ cylinder_radius * cos(2 * M_PI * u);
	//	each_pole.z = center.z
	//		+ cylinder_radius * sin(2 * M_PI * u);

	//	each_pole.y_start = 0.0f;
	//	each_pole.y_end = cylinder_height;

	//	each_pole_vector.push_back(each_pole);

	//}


	//constexpr GLuint floatsPerVertex = 3;
	//constexpr GLuint floatsPerUV = 2;

	//mesh.nIndices = v.size() / (floatsPerVertex + floatsPerUV);

	//glGenVertexArrays(1, &mesh.vao);
	//glBindVertexArray(mesh.vao);

	//// Create VBO
	//glGenBuffers(1, &mesh.vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer

	//glBufferData(
	//	GL_ARRAY_BUFFER,
	//	v.size() * sizeof(float),
	//	&v.front(),
	//	GL_STATIC_DRAW
	//); // Sends vertex or coordinate data to the GPU

	//// Strides between vertex coordinates
	//constexpr GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV);

	//// Create Vertex Attribute Pointers
	//glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, nullptr);
	//glEnableVertexAttribArray(0);

	//glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
	//glEnableVertexAttribArray(2);

	//UTranslator(mesh, p);





	// compile all that nonesense
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
	






	

	





	//// scale the object
	//mesh.scale = glm::scale(glm::vec3(p[4], p[5], p[6]));

	//// rotate the object (x, y, z) (0 - 6.4, to the right)
	//mesh.rotation = glm::rotate(p[7], glm::vec3(p[8], p[9], p[10]));

	//// move the object (x, y, z)
	//mesh.translation = glm::translate(glm::vec3(p[11], p[12], p[13]));

	//mesh.model = mesh.translation * mesh.rotation * mesh.scale;
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

