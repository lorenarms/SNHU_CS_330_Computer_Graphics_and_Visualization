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
	




	
		
}

