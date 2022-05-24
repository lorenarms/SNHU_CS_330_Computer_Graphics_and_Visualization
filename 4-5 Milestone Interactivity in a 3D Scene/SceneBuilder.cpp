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
/// </summary>
/// <param name="scene"></param>


	// PEN BODY
	GLMesh cyl_gMesh01;
	cyl_gMesh01.p = {
		0.5f, 0.0f, 0.5f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-90.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		2.0f, 0.0f, 0.0f,
		1.0f, 1.0f
	};
	cyl_gMesh01.length = 4.0f;	cyl_gMesh01.radius = 0.5f;	cyl_gMesh01.number_of_sides = 12.0f;
	cyl_gMesh01.texFilename = "textures\\white.png";
	ShapeBuilder::UBuildCylinder(cyl_gMesh01);
	scene.push_back(cyl_gMesh01);

	// PEN CLIP
	GLMesh cyl_gMesh02;
	cyl_gMesh02.p = {
		0.0f, 0.3f, 0.5f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-90.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.5f, 0.0f,
		1.0f, 1.0f
	};
	cyl_gMesh02.length = 1.0f;	cyl_gMesh02.radius = 0.1f;	cyl_gMesh02.number_of_sides = 12.0f;
	cyl_gMesh02.texFilename = "textures\\white.png";
	ShapeBuilder::UBuildCylinder(cyl_gMesh02);
	scene.push_back(cyl_gMesh02);

	// PEN BUTT
	GLMesh cyl_gMesh03;
	cyl_gMesh03.p = {
		0.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-90.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		2.1f, 0.025f, 0.0f,
		1.0f, 1.0f
	};
	cyl_gMesh03.length = 0.2f;	cyl_gMesh03.radius = 0.4f;	cyl_gMesh03.number_of_sides = 12.0f;
	cyl_gMesh03.texFilename = "textures\\white.png";
	ShapeBuilder::UBuildCylinder(cyl_gMesh03);
	scene.push_back(cyl_gMesh03);


	// PEN TIP
	GLMesh con_gMesh01;
	con_gMesh01.p = {
		0.2f, 0.1f, 0.3f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-90.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		-2.0f, 0.0f, 0.0f,
		1.0f, 1.0f
	};
	con_gMesh01.length = 1.0f;	con_gMesh01.radius = 0.5f;	con_gMesh01.number_of_sides = 12.0f;
	con_gMesh01.texFilename = "textures\\white.png";
	ShapeBuilder::UBuildCone(con_gMesh01);
	scene.push_back(con_gMesh01);

	GLMesh plan_gMesh01;
	plan_gMesh01.p = {
		0.0f, 0.2f, 0.3f, 1.0f,				// color r, g, b a
		4.0f, 8.0f, 4.0f,					// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,				// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,				// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f,					// translate x, y, z
		1.0f, 1.0f
	};

	plan_gMesh01.texFilename = "textures\\white.png";
	ShapeBuilder::UBuildPlane(plan_gMesh01);
	scene.push_back(plan_gMesh01);


}

