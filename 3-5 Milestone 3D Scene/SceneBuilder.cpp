/*
 * This class allows complete encapsulation of the program
 *
 * The user need only add a shape via the pattern shown in the
 * examples below, modifying properties (p) and the texture;
 * the ShapeBuilder class will handle the vertex calculations
 * and mesh construction
 *
 */



#include "SceneBuilder.h"
#include "ShapeBuilder.h"
#include "Mesh.h"

using namespace std;

void SceneBuilder::UBuildScene(vector<GLMesh>& scene)
{
	
	// seed the rand() function once
	srand(time(nullptr));

	

	// CONE - tip of the pen
	GLMesh con_mesh_01;
	con_mesh_01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		1.0f, 1.0f, 2.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.5f, 0.2f, 3.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	con_mesh_01.height = 1.0f;
	con_mesh_01.radius = 0.5f;
	con_mesh_01.length = 0.5f;
	con_mesh_01.number_of_sides = 24.0f;
	con_mesh_01.texFilename = "texture\\white.png";
	ShapeBuilder::UBuildRainbowCone(con_mesh_01, rand() % 100);
	scene.push_back(con_mesh_01);

	// CYLINDER - body of the pen
	GLMesh cyl_mesh_01;
	cyl_mesh_01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		1.0f, 1.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.5f, 0.2f, -3.0f,					// translate x, y, z
		1.0f, 1.0f
	};

	cyl_mesh_01.height = 1.0f;
	cyl_mesh_01.length = 6.0f;
	cyl_mesh_01.radius = 0.5f;
	cyl_mesh_01.number_of_sides = 24.0f;
	cyl_mesh_01.texFilename = "texture\\white.png";;
	ShapeBuilder::UBuildRainbowCylinder(cyl_mesh_01, rand() % 100);
	scene.push_back(cyl_mesh_01);

	// CLYLINDER - clip of the pen
	GLMesh cyl_mesh_02;
	cyl_mesh_02.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		0.2f, 0.2f, 2.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.1f, 1.1f, -1.8f,					// translate x, y, z
		1.0f, 1.0f
	};
	cyl_mesh_02.height = 1.0f;
	cyl_mesh_02.length = 1.0f;
	cyl_mesh_02.radius = 0.5f;
	cyl_mesh_02.number_of_sides = 12.0f;
	cyl_mesh_02.texFilename = "texture\\white.png";
	ShapeBuilder::UBuildRainbowCylinder(cyl_mesh_02, rand() % 100);
	scene.push_back(cyl_mesh_02);
	


	// CYLINDER - clicker of the pen
	GLMesh cyl_mesh_03;
	cyl_mesh_03.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		1.0f, 1.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.5f, 0.2f, -3.1f,					// translate x, y, z
		1.0f, 1.0f
	};

	cyl_mesh_03.height = 1.0f;
	cyl_mesh_03.length = 0.1f;
	cyl_mesh_03.radius = 0.4f;
	cyl_mesh_03.number_of_sides = 24.0f;
	cyl_mesh_03.texFilename = "texture\\white.png";
	ShapeBuilder::UBuildRainbowCylinder(cyl_mesh_03, rand() % 100);
	scene.push_back(cyl_mesh_03);



	GLMesh con_mesh_02;
	con_mesh_02.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		1.0f, 1.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	con_mesh_02.height = 0.2f;
	con_mesh_02.radius = 0.2f;
	con_mesh_02.length = 0.2f;
	con_mesh_02.number_of_sides = 24.0f;
	con_mesh_02.texFilename = "texture\\white.png";
	ShapeBuilder::UBuildRainbowCone(con_mesh_02, rand() % 100);
	scene.push_back(con_mesh_02);
	
		
}

