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

void ShapeBuilder::UBuildCylinder(GLMesh& mesh, vector<float> p /*p*/,
	float r /*r*/, float l /*l*/)
{

	// change "STEP" to increase / decrease resolution of cylinder
	const float PI = 3.14f;
	const float STEP = 36;
	float sectorStep = 2.0f * PI / STEP;

	// track which vertex is being added, add origin index when appropriate (every two)
	int step = 0;
	int vert = 2;


	// origin vertex of top and bottom of cylinder (center point)
	vector<float> vertices = {
								0.0f, 0.0f, 0.0f, p[0], p[1], p[2], p[3],	// top origin
								0.0f, 0.0f, l * -1, p[0], p[1], p[2], p[3]	// bottom origin
	};

	// vectors for indices, sides of cylinder
	vector<int> index = { 0 };
	vector<int> sides;

	// build the top of the cylinder
	// used vectors so I could use "pushback" and have control over where points went
	for (int i = 0; i <= STEP * 2; ++i)
	{
		float sectorAngle = i * sectorStep;
		// vertex
		vertices.push_back(r * cos(sectorAngle)); // x
		vertices.push_back(r * sin(sectorAngle)); // y
		vertices.push_back(0.0f);						// z

		// color
		vertices.push_back(p[0]);
		vertices.push_back(p[1]);
		vertices.push_back(p[2]);
		vertices.push_back(p[3]);

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
	for (int i = 0; i <= STEP * 2; ++i)
	{
		float sectorAngle = i * sectorStep;
		vertices.push_back(r * cos(sectorAngle)); // x
		vertices.push_back(r * sin(sectorAngle)); // y
		vertices.push_back(l * -1);						// z

		// color
		vertices.push_back(p[0]);
		vertices.push_back(p[1]);
		vertices.push_back(p[2]);
		vertices.push_back(p[3]);
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
	for (int i = 0; i < vertices.size(); i++)
	{
		verts[i] = vertices[i];
	}

	// make an array for the indices
	GLushort indices[10000];
	for (int i = 0; i < index.size(); i++)
	{
		indices[i] = index[i];
	}





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
	






	

	UTranslator(mesh, p);






	// scale the object
	mesh.scale = glm::scale(glm::vec3(p[4], p[5], p[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(p[7], glm::vec3(p[8], p[9], p[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(p[11], p[12], p[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale;
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

