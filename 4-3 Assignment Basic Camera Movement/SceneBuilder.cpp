#include "SceneBuilder.h"
#include "ShapeBuilder.h"
#include "Mesh.h"

using namespace std;

void SceneBuilder::UBuildScene(vector<GLMesh>& scene)
{
	
// seed the rand() function once
	srand(time(nullptr));


	/// <summary>
	/// Build a pyramid on the left side of the view
	/// </summary>
	/// <param name="scene"></param>
	GLMesh pyr_gMesh01;
	pyr_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		2.0f, 1.0f, 2.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		45.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.5f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	pyr_gMesh01.height = 1.8f;
	pyr_gMesh01.texFilename = "textures\\white.png";
	ShapeBuilder::UBuildRainbowPyramid(pyr_gMesh01, rand() % 100 + 1);
	scene.push_back(pyr_gMesh01);

	/// <summary>
	/// Build a cube on the right side of the view
	/// </summary>
	/// <param name="scene"></param>
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
	cub_gMesh01.texFilename = "textures\\white.png";
	ShapeBuilder::UBuildRainbowCube(cub_gMesh01, rand() % 100 + 1);
	scene.push_back(cub_gMesh01);



	/// <summary>
	/// Build a cone behind the cube on the right side of the view
	/// </summary>
	/// <param name="scene"></param>
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
	con_gMesh01.texFilename = "textures\\white.png";
	ShapeBuilder::UBuildRainbowCone(con_gMesh01, rand() % 100 + 1);
	scene.push_back(con_gMesh01);



	

}

