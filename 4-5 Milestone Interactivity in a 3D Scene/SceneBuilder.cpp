#include "SceneBuilder.h"
#include "ShapeBuilder.h"
#include "Mesh.h"

using namespace std;

void SceneBuilder::UBuildScene(vector<GLMesh>& scene)
{
	// macro to handle texture file locations, for .exe file

	// define the folder location for all textures used
	// make sure all textures stored in this location
#define textureFolderLocation "C:\\Users\\Lawrence\\Git Repos\\SNHU_CS_330_Projects\\3-5 Milestone 3D Scene\\textures\\"

// define a concat function that takes the above location and concatenates the texture name together
#define concat(first, second) first second

// seed the rand() function once
	srand(time(nullptr));

	GLMesh pyr_gMesh01;
	pyr_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		1.0f, 1.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		45.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.5f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	pyr_gMesh01.height = 1.8f;
#define texture "white.bmp"
	pyr_gMesh01.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildRainbowPyramid(pyr_gMesh01, rand() % 100 + 1);
	scene.push_back(pyr_gMesh01);

	// SHAPE 2: Cube
	GLMesh cub_gMesh01;
	cub_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		1.0f, 1.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		-45.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		1.5f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};

	cub_gMesh01.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildRainbowCube(cub_gMesh01, rand() % 100 + 1);
	scene.push_back(cub_gMesh01);

	GLMesh con_gMesh01;
	con_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		-90.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.5f, 0.0f, -1.5f,					// translate x, y, z
		1.0f, 1.0f
	};
	con_gMesh01.length = 1.0f;	con_gMesh01.radius = 0.5f;	con_gMesh01.number_of_sides = 24.0f;
	//#define texture "rocks.png"
	con_gMesh01.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildRainbowCone(con_gMesh01, rand() % 100 + 1);
	scene.push_back(con_gMesh01);



	GLMesh cyl_gMesh01;
	cyl_gMesh01.height = 1.0f;
	cyl_gMesh01.radius = 0.5f;
	cyl_gMesh01.length = 1.0f;
	cyl_gMesh01.number_of_sides = 24.0f;
	cyl_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		-90.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		30.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		1.5f, 0.0f, -1.5f,					// translate x, y, z
		1.0f, 1.0f
	};

	//#define texture "white.bmp"

	cyl_gMesh01.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildRainbowCylinder(cyl_gMesh01, rand() % 100 + 1);
	scene.push_back(cyl_gMesh01);


	GLMesh plan_gMesh01;
	plan_gMesh01.p = {
		0.2f, 0.2f, 0.2f, 1.0f,				// color r, g, b a
		4.0f, 8.0f, 4.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f
	};

	plan_gMesh01.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildRainbowPlane(plan_gMesh01, 0);
	scene.push_back(plan_gMesh01);


}

