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
	// macro to handle texture file locations, for .exe file

	// define the folder location for all textures used
	// make sure all textures stored in this location
	#define textureFolderLocation "C:\\Users\\Lawrence\\Git Repos\\SNHU_CS_330_Projects\\3-5 Milestone 3D Scene\\textures\\"

	// define a concat function that takes the above location and concatenates the texture name together
	#define concat(first, second) first second

	// seed the rand() function once
	srand(time(nullptr));
	
	// SHAPE 1: Colored Cube
	GLMesh gMesh01;
	gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		45.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.5f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};
	gMesh01.height = 1.7f;
	//#define texture "white.bmp"
	#define texture "white.bmp"
	gMesh01.texFilename = concat(textureFolderLocation, texture);		// create the texture file location name
	ShapeBuilder::UBuildRainbowCube(gMesh01, (rand() % 100 + 1));		
	scene.push_back(gMesh01);
	// END SHAPE 1


	// SHAPE 2: Cube
	GLMesh gMesh02;
	gMesh02.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		-45.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		1.5f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};
	#define texture "angelina.png"
	gMesh02.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildCube(gMesh02);
	scene.push_back(gMesh02);
		
}

