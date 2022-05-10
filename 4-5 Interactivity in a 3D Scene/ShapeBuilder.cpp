//#include "ShapeBuilder.h"
//
//
//void UBuildPyramid(GLMesh& mesh, vector<float> properties)
//{
//
//	//coordinates and colors for triangles
//	//normalized to window
//	// Specifies normalized device coordinates (x,y,z) and color for square vertices
//	GLfloat verts[] =
//	{
//		// Vertex Positions    // Colors
//		 0.0f,  0.5f,  0.0f,   properties[0], properties[1], properties[2], properties[3], // top of pyramid, red
//		-0.5f, -0.5f, -0.5f,   properties[0], properties[1], properties[2], properties[3], // bottom left front
//		 0.5f, -0.5f, -0.5f,   properties[0], properties[1], properties[2], properties[3], // bottom right front
//
//		-0.5f, -0.5f,  0.5f,   properties[0], properties[1], properties[2], properties[3], // bottom left back
//		 0.5f, -0.5f,  0.5f,   properties[0], properties[1], properties[2], properties[3], // bottom right back
//
//	};
//
//	const GLushort indices[] = {
//		0, 1, 2,
//		0, 1, 3,
//		0, 3, 4,
//		0, 2, 4,
//		1, 2, 3,
//		2, 3, 4
//	};
//
//	glGenVertexArrays(1, &mesh.vao);
//	glBindVertexArray(mesh.vao);
//
//	//create 2 buffers
//	glGenBuffers(2, mesh.vbos);
//	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
//
//	mesh.nIndices = std::size(indices);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	//tells how many values for a vertex
//	const GLuint floatsPerVertex = 3;
//	//tells how many values for a color
//	const GLuint floatsPerColor = 4;
//
//	//(2 + 4) * 1 = 6 strides
//	//tells program that it'll need to hit 6 numbers before starting to draw the
//	//next vertex
//	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);
//
//	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
//	glEnableVertexAttribArray(1);
//
//
//
//	// scale the object
//	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));
//
//	// rotate the object (x, y, z) (0 - 6.4, to the right)
//	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));
//
//	// move the object (x, y, z)
//	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));
//
//	mesh.model = mesh.translation * mesh.rotation * mesh.scale;
//
//}
//void UBuildCylinder(GLMesh& mesh, vector<float> properties, float radius, float length)
//{
//	// change "STEP" to increase / decrease resolution of cylinder
//	const float PI = 3.14f;
//	const float STEP = 36;
//	float sectorStep = 2.0f * PI / STEP;
//
//	// track which vertex is being added, add origin index when appropriate (every two)
//	int step = 0;
//	int vert = 2;
//
//
//	// origin vertex of top and bottom of cylinder (center point)
//	vector<float> vertices = {
//								0.0f, 0.0f, 0.0f, properties[0], properties[1], properties[2], properties[3],	// top origin
//								0.0f, 0.0f, length * -1, properties[0], properties[1], properties[2], properties[3]	// bottom origin
//	};
//
//	// vectors for indices, sides of cylinder
//	vector<int> index = { 0 };
//	vector<int> sides;
//
//	// build the top of the cylinder
//	// used vectors so I could use "pushback" and have control over where points went
//	for (int i = 0; i <= STEP * 2; ++i)
//	{
//		float sectorAngle = i * sectorStep;
//		// vertex
//		vertices.push_back(radius * cos(sectorAngle)); // x
//		vertices.push_back(radius * sin(sectorAngle)); // y
//		vertices.push_back(0.0f);						// z
//
//		// color
//		vertices.push_back(properties[0]);
//		vertices.push_back(properties[1]);
//		vertices.push_back(properties[2]);
//		vertices.push_back(properties[3]);
//
//		// track the vertices to draw, track the sides to draw
//		index.push_back(vert);
//		sides.push_back(vert + 1);
//
//		// some maths to keep indices in proper order
//		vert++;
//		step++;
//
//		// add in the origin index every two  vertices so that it connects them
//		if (step == 2)
//		{
//			step = 0;
//			vert--;
//			index.push_back(0);
//
//			// more maths to keep the indices in proper order
//			sides.pop_back();
//		}
//
//	}
//
//	// more maths to keep indices in proper order
//	vert *= 2;
//	step = 0;
//
//	// set origin of bottom disk triangle fan
//	index.push_back(1);
//
//	// build bottom triangle fan of cylinder
//	// same algorithm as above for top
//	for (int i = 0; i <= STEP * 2; ++i)
//	{
//		float sectorAngle = i * sectorStep;
//		vertices.push_back(radius * cos(sectorAngle)); // x
//		vertices.push_back(radius * sin(sectorAngle)); // y
//		vertices.push_back(length * -1);						// z
//
//		// color
//		vertices.push_back(properties[0]);
//		vertices.push_back(properties[1]);
//		vertices.push_back(properties[2]);
//		vertices.push_back(properties[3]);
//		index.push_back(vert);
//		sides.push_back(vert - 1);
//
//		// maths
//		vert++;
//		step++;
//		if (step == 2)
//		{
//			step = 0;
//			vert--;
//			index.push_back(1);
//			sides.pop_back();
//		}
//	}
//
//	// remove the very last entry from the index array, tis' not needed
//	index.pop_back();
//
//	// list the indexes to draw the sides
//	for (auto i = 0; i < sides.size() / 2 - 1; i++)
//	{
//		// lots of weird locations to find the given indices
//		index.push_back(sides[i]);
//		index.push_back(sides[i + 1]);
//		index.push_back(sides[sides.size() / 2 + i]);
//
//		index.push_back(sides[sides.size() / 2 + i]);
//		index.push_back(sides[sides.size() / 2 + i + 1]);
//		index.push_back(sides[i + 1]);
//
//
//	}
//
//	// okay all done! whew!
//	// make an array of vertices
//	// there doesn't seem to be an efficient way to convert from a vector to an array :(
//
//	GLfloat verts[10000];
//	for (int i = 0; i < vertices.size(); i++)
//	{
//		verts[i] = vertices[i];
//	}
//
//	// make an array for the indices
//	GLushort indices[10000];
//	for (int i = 0; i < index.size(); i++)
//	{
//		indices[i] = index[i];
//	}
//
//	// compile all that nonesense
//
//	glGenVertexArrays(1, &mesh.vao);
//	glBindVertexArray(mesh.vao);
//
//	//create 2 buffers
//	glGenBuffers(2, mesh.vbos);
//	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
//
//	// can this function take any other type of input? array's aren't very good imo
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
//
//	mesh.nIndices = std::size(indices);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	//tells how many values for a vertex
//	const GLuint floatsPerVertex = 3;
//	//tells how many values for a color
//	const GLuint floatsPerColor = 4;
//
//	//(2 + 4) * 1 = 6 strides
//	//tells program that it'll need to hit 6 numbers before starting to draw the
//	//next vertex
//	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);
//
//	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
//	glEnableVertexAttribArray(1);
//
//
//	// scale the object
//	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));
//
//	// rotate the object (x, y, z) (0 - 6.4, to the right)
//	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));
//
//	// move the object (x, y, z)
//	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));
//
//	mesh.model = mesh.translation * mesh.rotation * mesh.scale;
//}
//void UBuildCone(GLMesh& mesh, vector<float> properties, float radius, float length)
//{
//	// this is the same algorithm as the cylinder
//	// i plain run out of time to tweak it :(
//	// so it's a little rough and big on memory
//
//	const float PI = 3.14f;
//	const float STEP = 36;
//	float sectorStep = 2.0f * PI / STEP;
//
//	// track which vertex is being added, add origin index when appropriate (every two)
//	int step = 0;
//	int vert = 2;
//
//	vector<float> vertices = {
//								0.0f, 0.0f, 0.0f, properties[0], properties[1], properties[2], properties[3],	// top origin
//								0.0f, 0.0f, length * -1, properties[0], properties[1], properties[2], properties[3]	// bottom origin
//	};
//
//	vector<int> index = { 0, 1 };
//	vector<int> sides;
//
//	//build the top of the cylinder
//	for (int i = 0; i <= STEP * 2; ++i)
//	{
//		float sectorAngle = i * sectorStep;
//		// vertex
//		vertices.push_back(radius * cos(sectorAngle)); // x
//		vertices.push_back(radius * sin(sectorAngle)); // y
//		vertices.push_back(0.0f);						// z
//
//		// color
//		vertices.push_back(properties[0]);
//		vertices.push_back(properties[1]);
//		vertices.push_back(properties[2]);
//		vertices.push_back(properties[3]);
//		index.push_back(vert);
//		sides.push_back(vert + 1);
//
//		vert++;
//		step++;
//		if (step == 2)
//		{
//			step = 0;
//			vert--;
//			index.push_back(0);
//			sides.pop_back();
//		}
//
//	}
//
//	// skip ahead to the next set of vertices
//	vert *= 2;
//	step = 0;
//	// set origin of bottom disk triangle fan
//	index.push_back(1);
//
//	// build bottom triangle fan of cylinder
//	for (int i = 0; i <= STEP * 2; ++i)
//	{
//		float sectorAngle = i * sectorStep;
//		vertices.push_back(radius * cos(sectorAngle)); // x
//		vertices.push_back(radius * sin(sectorAngle)); // y
//		vertices.push_back(0.0f);						// z
//
//		// color
//		vertices.push_back(properties[0]);
//		vertices.push_back(properties[1]);
//		vertices.push_back(properties[2]);
//		vertices.push_back(properties[3]);
//		index.push_back(vert);
//		sides.push_back(vert - 1);
//		//sides.push_back(vert);
//
//		vert++;
//		step++;
//		if (step == 2)
//		{
//			step = 0;
//			vert--;
//			index.push_back(1);
//			sides.pop_back();
//		}
//	}
//	// remove the very last entry from the index array, tis' not needed
//	index.pop_back();
//
//
//
//	GLfloat verts[10000];
//
//	for (int i = 0; i < vertices.size(); i++)
//	{
//		verts[i] = vertices[i];
//	}
//
//	GLushort indices[10000];
//
//	for (int i = 0; i < index.size(); i++)
//	{
//		indices[i] = index[i];
//	}
//
//
//
//	glGenVertexArrays(1, &mesh.vao);
//	glBindVertexArray(mesh.vao);
//
//	//create 2 buffers
//	glGenBuffers(2, mesh.vbos);
//	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
//
//	mesh.nIndices = std::size(indices);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	//tells how many values for a vertex
//	const GLuint floatsPerVertex = 3;
//	//tells how many values for a color
//	const GLuint floatsPerColor = 4;
//
//	//(2 + 4) * 1 = 6 strides
//	//tells program that it'll need to hit 6 numbers before starting to draw the
//	//next vertex
//	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);
//
//	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
//	glEnableVertexAttribArray(1);
//
//
//
//	// scale the object
//	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));
//
//	// rotate the object (x, y, z) (0 - 6.4, to the right)
//	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));
//
//	// move the object (x, y, z)
//	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));
//
//	mesh.model = mesh.translation * mesh.rotation * mesh.scale;
//}
//void UBuildPlane(GLMesh& mesh, vector<float> properties)
//{
//
//	//coordinates and colors for triangles
//	//normalized to window
//	// Specifies normalized device coordinates (x,y,z) and color for square vertices
//	GLfloat verts[] =
//	{
//		// Vertex Positions    // Colors
//		 5.0f,  0.0f,  5.0f,   properties[0], properties[1], properties[2], properties[3],
//		 5.0f,  0.0f, -5.0f,   properties[0], properties[1], properties[2], properties[3],
//		-5.0f,  0.0f,  5.0f,   properties[0], properties[1], properties[2], properties[3],
//		-5.0f,  0.0f, -5.0f,   properties[0], properties[1], properties[2], properties[3]
//
//	};
//
//	const GLushort indices[] = {
//		0, 1, 2, 1, 2, 3
//	};
//
//	glGenVertexArrays(1, &mesh.vao);
//	glBindVertexArray(mesh.vao);
//
//	//create 2 buffers
//	glGenBuffers(2, mesh.vbos);
//	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
//
//	mesh.nIndices = std::size(indices);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	//tells how many values for a vertex
//	const GLuint floatsPerVertex = 3;
//	//tells how many values for a color
//	const GLuint floatsPerColor = 4;
//
//	//(2 + 4) * 1 = 6 strides
//	//tells program that it'll need to hit 6 numbers before starting to draw the
//	//next vertex
//	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);
//
//	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
//	glEnableVertexAttribArray(1);
//
//
//
//	// scale the object
//	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));
//
//	// rotate the object (x, y, z) (0 - 6.4, to the right)
//	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));
//
//	// move the object (x, y, z)
//	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));
//
//	mesh.model = mesh.translation * mesh.rotation * mesh.scale;
//
//}
