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
	#define textureFolderLocation "C:\\Users\\Lawrence\\Git Repos\\SNHU_CS_330_Projects\\3-3 Building a 3D Pyramid\\textures\\"

	// define a concat function that takes the above location and concatenates the texture name together
	#define concat(first, second) first second

	// seed the rand() function once
	srand(time(nullptr));
	
	// SHAPE 1: Colored Pyramid
	GLMesh gMesh01;
	gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		1.0f, 1.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		35.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};
	gMesh01.height = 1.7f;
	//#define texture "white.bmp"
	#define texture "white.bmp"
	gMesh01.texFilename = concat(textureFolderLocation, texture);		// create the texture file location name
	ShapeBuilder::UBuildRainbowPyramid(gMesh01, (rand() % 100 + 1));		
	scene.push_back(gMesh01);
	// END SHAPE 1


	// SHAPE 2: Colored Pyramid
	GLMesh gMesh02;
	gMesh02.p = {
		1.0f,	1.0f,	1.0f,	1.0f,		// color r, g, b, a
		1.0f,	1.0f,	1.0f,				// scale x, y z
		0.0f,	1.0f,	0.0f,	0.0f,		// x amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		35.0f,	0.0f,	1.0f,	0.0f,		// y amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		0.0f,	0.0f,	0.0f,	1.0f,		// z amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		2.0f,	0.0f,	1.0f,				// translate x, y, z
		1.0f,	1.0f						// texture scaling
	};
	gMesh02.height = 1.7f;
	#define texture "white.bmp"
	gMesh02.texFilename = concat(textureFolderLocation, texture);
	//ShapeBuilder::UBuildPyramid(gMesh02);
	ShapeBuilder::UBuildRainbowPyramid(gMesh02, (rand() % 100 + 1));
	scene.push_back(gMesh02);
	// END SHAPE 2


	// SHAPE 3: Colored Pyramid
	GLMesh gMesh03;
	gMesh03.p = {
		1.0f,	1.0f,	1.0f,	1.0f,		// color r, g, b, a
		1.0f,	1.0f,	1.0f,				// scale x, y z
		0.0f,	1.0f,	0.0f,	0.0f,		// x amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		35.0f,	0.0f,	1.0f,	0.0f,		// y amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		0.0f,	0.0f,	0.0f,	1.0f,		// z amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		-2.0f,	0.0f,	-1.0f,				// translate x, y, z
		1.0f,	1.0f						// texture scaling
	};
	gMesh03.height = 1.7f;
	#define texture "white.bmp"
	gMesh03.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildRainbowPyramid(gMesh03, (rand() % 100 + 1));
	scene.push_back(gMesh03);
	// END SHAPE 3


}

