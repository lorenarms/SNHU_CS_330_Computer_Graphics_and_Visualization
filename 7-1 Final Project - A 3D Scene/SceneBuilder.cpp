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




// PEN BODY
	GLMesh cyl_gMesh01;
	cyl_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 1.0f, 0.25f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.10f, 3.0f,
		1.0f, 1.0f
	};
	cyl_gMesh01.height = 4.0f;	cyl_gMesh01.radius = 0.5f;	cyl_gMesh01.number_of_sides = 128.0f;
	cyl_gMesh01.texFilename = "textures\\pen_body.png";
	ShapeBuilder::UBuildCylinder(cyl_gMesh01);
	scene.push_back(cyl_gMesh01);



	// PEN CLIP
	GLMesh cyl_gMesh02;
	cyl_gMesh02.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 1.0f, 0.02f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		-45.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		-0.063f, 0.22f, 2.5f,
		1.0f, 1.0f
	};
	cyl_gMesh02.height = 1.5f;	cyl_gMesh02.radius = 0.4f;	cyl_gMesh02.number_of_sides = 16.0f;
	cyl_gMesh02.texFilename = "textures\\goldmetal.png";
	ShapeBuilder::UBuildCylinder(cyl_gMesh02);
	scene.push_back(cyl_gMesh02);



	// PEN BUTT
	GLMesh cyl_gMesh03;
	cyl_gMesh03.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 1.0f, 0.25f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.10f, 3.05f,
		1.0f, 1.0f
	};

	cyl_gMesh03.height = 3.0f;	cyl_gMesh03.radius = 0.45f;	cyl_gMesh03.number_of_sides = 128.0f;
	cyl_gMesh03.texFilename = "textures\\grey.png";
	ShapeBuilder::UBuildCylinder(cyl_gMesh03);
	scene.push_back(cyl_gMesh03);


	// PEN TIP
	GLMesh con_gMesh01;
	con_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 0.5f, 0.25f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.10f, -1.0f,
		1.0f, 1.0f
	};
	con_gMesh01.height = 1.0f;	con_gMesh01.radius = 0.5f;	con_gMesh01.number_of_sides = 128.0f;
	con_gMesh01.texFilename = "textures\\pen_tip.png";
	ShapeBuilder::UBuildCone(con_gMesh01);
	scene.push_back(con_gMesh01);



	// DESK
	GLMesh plan_gMesh01;
	plan_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,				// color r, g, b a
		16.0f, 2.0f, 16.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		45.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		1.0f, 0.0f, 0.0f,					// translate x, y, z
		2.0f, 2.0f
	};
	plan_gMesh01.texFilename = "textures\\desk.png";
	ShapeBuilder::UBuildPlane(plan_gMesh01);
	scene.push_back(plan_gMesh01);


	// TABLET
	GLMesh tablet_gMesh01;
	tablet_gMesh01.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		8.0f,	0.1f,	6.0f,
		0.0f,	1.0f,	0.0f,	0.0f,
		55.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		0.0f,	0.0f,	0.0f,
		1.0f,	1.0f
	};
	tablet_gMesh01.texFilename = "textures\\tablet.png";
	ShapeBuilder::UBuildCube(tablet_gMesh01);
	scene.push_back(tablet_gMesh01);


	//RUBIK'S CUBE
	GLMesh rubiks_gMesh01;
	rubiks_gMesh01.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		1.4f,	1.4f,	1.4f,
		0.0f,	1.0f,	0.0f,	0.0f,
		-110.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		2.0f,	0.1f,	-2.0f,
		1.0f,	1.0f
	};
	rubiks_gMesh01.texFilename = "textures\\rubiks.png";
	ShapeBuilder::UBuildCube(rubiks_gMesh01);
	scene.push_back(rubiks_gMesh01);


	//HOLLOW CYLINDER
	GLMesh hollow_cyl;
	hollow_cyl.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		2.0f,	2.0f,	2.0f,
		0.0f,	1.0f,	0.0f,	0.0f,
		-90.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		-4.0f,	0.0f,	3.0f,
		1.0f,	1.0f
	};
	hollow_cyl.texFilename = "textures\\coffee_cup.png";
	hollow_cyl.innerRadius = 0.45f;
	hollow_cyl.radius = 0.5f;
	hollow_cyl.height = 1.0f;
	hollow_cyl.number_of_sides = 144.0f;
	ShapeBuilder::UBuildHollowCylinder(hollow_cyl);
	scene.push_back(hollow_cyl);

	// COFFEE
	GLMesh coffee;
	coffee.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		2.0f,	2.0f,	2.0f,
		0.0f,	1.0f,	0.0f,	0.0f,
		180.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		-4.0f,	1.9f,	5.0f,
		1.0f,	1.0f
	};
	coffee.radius = 0.45f;
	coffee.number_of_sides = 144.0f;
	coffee.texFilename = "textures\\coffee.png";
	ShapeBuilder::UBuildCircle(coffee);
	scene.push_back(coffee);


	// HANDLE
	GLMesh handle;
	handle.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		2.0f,	2.0f,	2.0f,
		90.0f,	1.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		-5.0f,	2.0f,	4.0f,
		1.0f,	1.0f
	};
	handle.texFilename = "textures\\white.png";
	handle.innerRadius = 0.3f;
	handle.radius = 0.4f;
	handle.height = 0.1f;
	handle.number_of_sides = 144.0f;
	ShapeBuilder::UBuildHollowCylinder(handle);
	scene.push_back(handle);


	// KISS 1
	GLMesh kissTop_01;
	kissTop_01.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		0.8f,	0.8f,	0.8f,
		0.0f,	1.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		-2.0f,	0.18f,	1.0f,
		1.0f,	1.0f
	};
	kissTop_01.height = 0.8f;
	kissTop_01.radius = 0.5;
	kissTop_01.number_of_sides = 144.0f;
	kissTop_01.texFilename = "textures\\kiss.png";
	ShapeBuilder::UBuildCone(kissTop_01);
	scene.push_back(kissTop_01);

	// KISS 1
	GLMesh kissBottom_01;
	kissBottom_01.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		0.8f,	0.8f,	0.8f,
		0.0f,	1.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		-2.0f,	0.1f,	1.0f,
		1.0f,	1.0f
	};
	kissBottom_01.height = 0.1f;
	kissBottom_01.radius = 0.5;
	kissBottom_01.number_of_sides = 144.0f;
	kissBottom_01.texFilename = "textures\\kiss_sides.png";
	ShapeBuilder::UBuildCylinder(kissBottom_01);
	scene.push_back(kissBottom_01);

	// KISS 1 FLAG
	GLMesh kissFlag_01;
	kissFlag_01.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		0.7f,	0.7f,	0.05f,
		90.0f,	1.0f,	0.0f,	0.0f,
		90.0f,	0.0f,	1.0f,	0.0f,
		180.0f,	0.0f,	0.0f,	1.0f,
		-1.6f,	1.0f,	1.4f,
		1.0f,	1.0f
	};
	kissFlag_01.texFilename = "textures\\kiss_flag.png";
	ShapeBuilder::UBuildPlane(kissFlag_01);
	scene.push_back(kissFlag_01);


	// KISS 2
	GLMesh kissTop_02;
	kissTop_02.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		0.8f,	0.8f,	0.8f,
		0.0f,	1.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		-2.0f,	0.18f,	-1.0f,
		1.0f,	1.0f
	};
	kissTop_02.height = 0.8f;
	kissTop_02.radius = 0.5;
	kissTop_02.number_of_sides = 144.0f;
	kissTop_02.texFilename = "textures\\kiss.png";
	ShapeBuilder::UBuildCone(kissTop_02);
	scene.push_back(kissTop_02);

	// KISS 2
	GLMesh kissBottom_02;
	kissBottom_02.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		0.8f,	0.8f,	0.8f,
		0.0f,	1.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		-2.0f,	0.1f,	-1.0f,
		1.0f,	1.0f
	};
	kissBottom_02.height = 0.1f;
	kissBottom_02.radius = 0.5;
	kissBottom_02.number_of_sides = 144.0f;
	kissBottom_02.texFilename = "textures\\kiss_sides.png";
	ShapeBuilder::UBuildCylinder(kissBottom_02);
	scene.push_back(kissBottom_02);

	// KISS 2 FLAG
	GLMesh kissFlag_02;
	kissFlag_02.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		0.7f,	0.7f,	0.05f,
		90.0f,	1.0f,	0.0f,	0.0f,
		90.0f,	0.0f,	1.0f,	0.0f,
		180.0f,	0.0f,	0.0f,	1.0f,
		-1.6f,	1.0f,	-0.6f,
		1.0f,	1.0f
	};
	kissFlag_02.texFilename = "textures\\kiss_flag.png";
	ShapeBuilder::UBuildPlane(kissFlag_02);
	scene.push_back(kissFlag_02);

	// KISS 3
	GLMesh kissTop_03;
	kissTop_03.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		0.8f,	0.8f,	0.8f,
		0.0f,	1.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		-3.0f,	0.18f,	0.0f,
		1.0f,	1.0f
	};
	kissTop_03.height = 0.8f;
	kissTop_03.radius = 0.5;
	kissTop_03.number_of_sides = 144.0f;
	kissTop_03.texFilename = "textures\\kiss.png";
	ShapeBuilder::UBuildCone(kissTop_03);
	scene.push_back(kissTop_03);

	// KISS 3
	GLMesh kissBottom_03;
	kissBottom_03.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		0.8f,	0.8f,	0.8f,
		0.0f,	1.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		-3.0f,	0.1f,	0.0f,
		1.0f,	1.0f
	};
	kissBottom_03.height = 0.1f;
	kissBottom_03.radius = 0.5;
	kissBottom_03.number_of_sides = 144.0f;
	kissBottom_03.texFilename = "textures\\kiss_sides.png";
	ShapeBuilder::UBuildCylinder(kissBottom_03);
	scene.push_back(kissBottom_03);

	// KISS 3 FLAG
	GLMesh kissFlag_03;
	kissFlag_03.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		0.7f,	0.7f,	0.05f,
		90.0f,	1.0f,	0.0f,	0.0f,
		90.0f,	0.0f,	1.0f,	0.0f,
		180.0f,	0.0f,	0.0f,	1.0f,
		-2.6f,	1.0f,	0.4f,
		1.0f,	1.0f
	};
	kissFlag_03.texFilename = "textures\\kiss_flag.png";
	ShapeBuilder::UBuildPlane(kissFlag_03);
	scene.push_back(kissFlag_03);

}

