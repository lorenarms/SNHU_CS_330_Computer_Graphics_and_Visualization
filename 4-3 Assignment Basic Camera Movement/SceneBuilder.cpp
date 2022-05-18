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

	GLMesh gMesh03;
	gMesh03.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		45.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.5f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	gMesh03.height = 0.8f;
#define texture "bricks.png"
	gMesh03.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildPyramid(gMesh03);
	scene.push_back(gMesh03);

	// SHAPE 2: Cube
	GLMesh gMesh02;
	gMesh02.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		1.0f, 1.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		-45.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		1.5f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};
#define texture "rubiks.png"
	gMesh02.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildCube(gMesh02);
	scene.push_back(gMesh02);

	GLMesh gMesh01;
	gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		-90.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.5f, 0.0f, -1.5f,					// translate x, y, z
		1.0f, 1.0f
	};
	gMesh01.length = 1.0f;	gMesh01.radius = 0.5f;	gMesh01.number_of_sides = 12.0f;
#define texture "pyramid01.png"
	//#define texture "rocks.png"
	gMesh01.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildCone(gMesh01);
	scene.push_back(gMesh01);



	GLMesh cyl_gMesh;
	cyl_gMesh.height = 1.0f;
	cyl_gMesh.radius = 0.5f;
	cyl_gMesh.length = 1.0f;
	cyl_gMesh.number_of_sides = 12.0f;
	cyl_gMesh.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		-90.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		30.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		1.5f, 0.0f, -1.5f,					// translate x, y, z
		1.0f, 1.0f
	};
#define texture "rocks.png"
	//#define texture "white.bmp"

	cyl_gMesh.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildCylinder(cyl_gMesh);
	scene.push_back(cyl_gMesh);


	GLMesh plan_gMesh;
	plan_gMesh.p = {
		0.2f, 0.2f, 0.2f, 1.0f,				// color r, g, b a
		4.0f, 8.0f, 4.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f
	};
#define texture "walltexture.png"

	plan_gMesh.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildPlane(plan_gMesh);
	scene.push_back(plan_gMesh);


}

