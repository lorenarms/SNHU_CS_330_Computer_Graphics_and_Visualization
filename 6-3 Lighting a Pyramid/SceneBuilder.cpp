///
///	This class is designed to be the one place where all
///	shapes are created. It utilizes the UShapeBuilder class
///	to build the shapes into GLMesh structs. The individual
///	shape structs are then added to a vector called "scene" that is
///	then passed to the main render method in the source class
///	(5-3 Texturing a Pyramid.cpp)
///
///
///	Follow the standard shown below in the <summary> to see
///	how to build a shape
///




#include "SceneBuilder.h"
#include "ShapeBuilder.h"
#include "Mesh.h"

using namespace std;


void SceneBuilder::UBuildScene(vector<GLMesh>& scene)
{




	// seed the rand() function once
	srand(time(nullptr));


	/// <summary>
	///
	///BUILDING A SHAPE:
	///To build a shape, follow the following standard:
	///
	///		GLMesh <glmesh_name>
	///		<glmesh_name>.p = {
	///		red float, green float, blue float, alpha float,
	///		x scale float, y scale float, z scale float,
	///		x rotation degrees float, 1.0f, 0.0f, 0.0f,
	///		y rotation degrees float, 0.0f, 1.0f, 0.0f,
	///		z rotation degrees float, 0.0f, 0.0f, 1.0f,
	///		x translate float, y translate float, z translate float,
	///		x texture scale float, y texture scale float
	///		};
	///		<glmesh_name>.texFilename = "textures\\[filename.filetype]";
	///		<glmesh_name>.length = float;
	///		<glmesh_name>.height = float;
	///		<glmesh_name>.radius = float;
	///		<glmesh_name>.number_of_sides = float;
	///		ShapeBuilder::<ShapeBuilderMethod>(<glmesh_name>);
	///		**OR**
	///		ShapeBuilder::<ShapeBuild "Rainbow" Shape>(<glmesh_name>, rand() % 100 + 1);
	///		scene.push_back(<glmesh_name>);
	///
	///
	///
	///		See below for an example using the UBuildCone() method
	///
	///
	/// </summary>
	/// <param name="scene"></param>






	//	PYRAMID 01
	GLMesh pyr_mesh_realBricks;
	pyr_mesh_realBricks.p = {
		1.0f, 1.0f, 1.0f, 0.0f,				// color r, g, b a
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	pyr_mesh_realBricks.height = 0.8f;
	pyr_mesh_realBricks.length = 0.5f;
	pyr_mesh_realBricks.radius = 0.5f;
	pyr_mesh_realBricks.number_of_sides = 12.0f;
	pyr_mesh_realBricks.texFilename = "textures\\realbricks.png";
	ShapeBuilder::UBuildPyramid(pyr_mesh_realBricks);
	scene.push_back(pyr_mesh_realBricks);



	//	PYRAMID 02
	GLMesh pyr_mesh_pyramidBricks;
	pyr_mesh_pyramidBricks.p = {
		1.0f, 1.0f, 1.0f, 0.0f,				// color r, g, b a
		2.5f, 2.5f, 2.5f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		-1.0f, 0.0f, 4.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	pyr_mesh_pyramidBricks.height = 0.8f;
	pyr_mesh_pyramidBricks.texFilename = "textures\\pyramid.png";
	ShapeBuilder::UBuildPyramid(pyr_mesh_pyramidBricks);
	scene.push_back(pyr_mesh_pyramidBricks);


	// PYRAMID 03
	GLMesh pyr_mesh_cartoonBricks;
	pyr_mesh_cartoonBricks.p = {
		1.0f, 1.0f, 1.0f, 0.0f,				// color r, g, b a
		2.0f, 2.0f, 2.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		4.0f, 0.0f, -1.5f,					// translate x, y, z
		1.0f, 1.0f
	};
	pyr_mesh_cartoonBricks.height = 0.8f;
	pyr_mesh_cartoonBricks.texFilename = "textures\\bricks.png";
	ShapeBuilder::UBuildPyramid(pyr_mesh_cartoonBricks);
	scene.push_back(pyr_mesh_cartoonBricks);


	// GROUND
	GLMesh mesh;
	mesh.p = {
		0.0f, 1.0f, 0.0f, 0.0f,				// color r, g, b a
		5.0f, 5.0f, 5.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	mesh.texFilename = "textures\\dunes.jpg";
	ShapeBuilder::UBuildPlane(mesh);
	scene.push_back(mesh);


}

