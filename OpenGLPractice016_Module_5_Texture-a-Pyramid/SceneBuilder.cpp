#include "SceneBuilder.h"
#include "ShapeBuilder.h"
#include "Mesh.h"

using namespace std;

void SceneBuilder::UBuildScene(vector<GLMesh>& scene)
{
	
	// SHAPE 1: PYRAMID
	GLMesh gMesh01;
	gMesh01.p = {
		0.5f, 0.0f, 0.8f, 1.0f,				// color r, g, b a	
		1.0f, 1.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};
	gMesh01.height = 1.7f;
	gMesh01.texFilename = "bricks.png";
	ShapeBuilder::UBuildPyramid(gMesh01);
	scene.push_back(gMesh01);
		

	// SHAPE 2: CONE
	GLMesh gMesh02;
	gMesh02.p = {
		0.0f,	0.0f,	0.0f,	1.0f,		// color r, g, b, a
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
	gMesh02.texFilename = "pyramid_tex.jpg";
	ShapeBuilder::UBuildCone(gMesh02);
	scene.push_back(gMesh02);


	// SHAPE 3: Triangle Trial
	GLMesh gMesh03;
	gMesh03.p = {
		0.5f, 0.0f, 0.8f, 1.0f,				// color r, g, b a	
		1.0f, 2.0f, 1.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.0f, 2.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f							// texture scaling
	};
	gMesh03.radius = 1.0;
	gMesh03.height = 1.7f;
	gMesh03.texFilename = "angelina.png";
	ShapeBuilder::UBuildTriangles(gMesh03);
	scene.push_back(gMesh03);


	// SHAPE 4: CYLINDER
	GLMesh gMesh04;
	gMesh04.p = {
		0.5f, 0.0f, 0.8f, 1.0f,				// color r, g, b a	
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-3.5f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	gMesh04.radius = 0.5f;
	gMesh04.height = 1.0f;
	gMesh04.length = 1.0f;
	gMesh04.number_of_sides = 24.0f;
	gMesh04.texFilename = "angelina.png";
	ShapeBuilder::UBuildCylinder(gMesh04);
	scene.push_back(gMesh04);


}

