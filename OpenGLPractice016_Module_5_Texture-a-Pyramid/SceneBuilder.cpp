#include "SceneBuilder.h"
#include "ShapeBuilder.h"
#include "Mesh.h"

using namespace std;

void SceneBuilder::UBuildScene(vector<GLMesh>& scene)
{
	// define the folder location for all textures used
	// make sure all textures stored in this location
	#define textureFolderLocation "C:\\Users\\Lawrence\\Git Repos\\SNHU_CS_330_Projects\\OpenGLPractice016_Module_5_Texture-a-Pyramid\\textures\\"

	// define a concat function that takes the above location and concatenates the texture name together
	#define concat(first, second) first second
	
	
	// SHAPE 1: PYRAMID
	GLMesh gMesh01;
	gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		1.0f, 1.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};
	gMesh01.height = 1.7f;
	//#define texture "white.bmp"
	#define texture "bricks.png"
	gMesh01.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildPyramid(gMesh01);
	//ShapeBuilder::UBuildRainbowPyramid(gMesh01);
	scene.push_back(gMesh01);
		

	// SHAPE 2: CONE
	GLMesh gMesh02;
	gMesh02.p = {
		1.0f,	1.0f,	1.0f,	1.0f,		// color r, g, b, a
		1.0f,	1.0f,	1.0f,				// scale x, y z
		270.0f,	1.0f,	0.0f,	0.0f,		// x amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		0.0f,	0.0f,	1.0f,	0.0f,		// y amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		0.0f,	0.0f,	0.0f,	1.0f,		// z amount of rotation, rotate x, y, z, (0 - 6.4, to the right)
		2.0f,	0.0f,	0.0f,				// translate x, y, z
		1.0f,	1.0f						// texture scaling
	};
	gMesh02.radius = 1.0f;
	gMesh02.length = 1.7f;
	gMesh02.number_of_sides = 12.0f;
	#define texture "pyramid_tex.jpg"
	gMesh02.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildCone(gMesh02);
	scene.push_back(gMesh02);


	// SHAPE 3: Triangle Trial
	GLMesh gMesh03;
	gMesh03.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a	
		1.0f, 2.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.0f, 2.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};
	gMesh03.radius = 1.0;
	gMesh03.height = 1.7f;
	#define texture "angelina.png"
	gMesh03.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildPlane(gMesh03);
	scene.push_back(gMesh03);


	// SHAPE 4: CYLINDER
	GLMesh gMesh04;
	gMesh04.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a	
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		270.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-3.5f, 0.0f, 1.0f,					// translate x, y, z
		2.0f, 2.0f
	};
	gMesh04.radius = 0.5f;
	gMesh04.height = 1.0f;
	gMesh04.length = 1.0f;
	gMesh04.number_of_sides = 24.0f;
	#define texture "angelina.png"
	gMesh04.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildCylinder(gMesh04);
	scene.push_back(gMesh04);


	// SHAPE 5: CIRCLE
	GLMesh gMesh05;
	gMesh05.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a	
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		-45.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-4.5f, 0.0f, 2.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	gMesh05.radius = 0.5f;
	gMesh05.height = 1.0f;
	gMesh05.length = 1.0f;
	gMesh05.number_of_sides = 24.0f;
	#define texture "angelina.png"
	gMesh05.texFilename = concat(textureFolderLocation, texture);
	ShapeBuilder::UBuildCircle(gMesh05);
	scene.push_back(gMesh05);


}

