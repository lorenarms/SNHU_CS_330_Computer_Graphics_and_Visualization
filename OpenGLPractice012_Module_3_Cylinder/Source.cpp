//---------------------------------------------------
//
// Lawrence Artl
// CS-330 Comp Graphic and Viz
// Assignment 3-5
//
// 3D SCENE
//
//---------------------------------------------------


#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>



// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// shader program macros
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif


using namespace std;

//window title
const char* const WINDOW_TITLE = "Module 3 Assignment: 3D Scene";

//window width, height
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//GL data for mesh
struct GLMesh
{
	//vertex array
	GLuint vao;
	//vertex buffer
	GLuint vbos[2];
	//indices of the mesh
	GLuint nIndices;

	GLfloat verts[35];
};

//main window
GLFWwindow* gWindow = nullptr;
//triangle mesh data
GLMesh gMesh;
//shader program
GLuint gShaderProgram;




//initialize program
bool UInitialize(int, char* [], GLFWwindow** window);
//set window size
void UResizeWindow(GLFWwindow* window, int width, int height);
//process user input
void UProcessInput(GLFWwindow* window);
//render graphics
void UCreatePyramid(GLMesh& mesh);
void URender();
//compile shaders
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource,
	GLuint& programId);
//free up memory on close
void UDestroyMesh(GLMesh& mesh);
void UDestroyShaderProgram(GLuint programId);
void getUnitCircleVertices(float sectorCount, GLMesh& mesh);




// Vertex Shader Source Code
const GLchar* vertex_shader_source = GLSL(440,
	layout(location = 0) in vec3 position; // Vertex data from Vertex Attrib Pointer 0
layout(location = 1) in vec4 color;  // Color data from Vertex Attrib Pointer 1

out vec4 vertexColor; // variable to transfer color data to the fragment shader

//uniform mat4 shaderTransform; // 4x4 matrix variable for transforming vertex data
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f); // transforms vertex data using matrix
	vertexColor = color; // references incoming color data
}
);

// Fragment Shader Source Code
const GLchar* fragment_shader_source = GLSL(440,
	in vec4 vertexColor; // Variable to hold incoming color data from vertex shader

out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(vertexColor);
}
);



//main
int mainVoid(int argc, char* argv[])
{
	//check if initialized correctly
	if (!UInitialize(argc, argv, &gWindow))
		return EXIT_FAILURE;

	//create mesh, create vbo
	UCreatePyramid(gMesh);


	//build shader programs
	if (!UCreateShaderProgram(vertex_shader_source, fragment_shader_source,
		gShaderProgram))
		return EXIT_FAILURE;

	//bg color of window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//rendering loop
	//keep checking if window has closed
	while (!glfwWindowShouldClose(gWindow))
	{
		//process user input
		UProcessInput(gWindow);

		//render frame
		URender();

		glfwPollEvents();
	}


	//clean up
	UDestroyMesh(gMesh);
	UDestroyShaderProgram(gShaderProgram);

	//exit with success!
	exit(EXIT_SUCCESS);

}


//functions in order of use
//
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
	//initialize GLFW, GLEW, create window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	//use constants for vars
	*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	//window fails to be created
	if (*window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, UResizeWindow);

	//initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult)
	{
		std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
		return false;
	}

	return true;
}

void UCreatePyramid(GLMesh& mesh)
{
	//coordinates and colors for triangles
	//normalized to window
	// Specifies normalized device coordinates (x,y,z) and color for square vertices


	vector<float> verts;
	verts.push_back(0.0f);
	verts.push_back(0.5f);
	verts.push_back(0.0f);

	verts.push_back(-0.5f);
	verts.push_back(-0.5f);
	verts.push_back(-0.5f);

	verts.push_back(0.5f);
	verts.push_back(-0.5f);
	verts.push_back(-0.5f);

	verts.push_back(1.0f);
	verts.push_back(0.0f);
	verts.push_back(1.0f);
	verts.push_back(1.0f);
	

	GLfloat vertices[21];

	
	
	//GLfloat vertices[] =
	//{
	//	// Vertex Positions    // Colors
	//	 0.0f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f, 1.0f, // top of pyramid, red
	//	-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f, // bottom left front
	//	 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, 1.0f, // bottom right front

	//	-0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f, 1.0f, // bottom left back
	//	 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f, 1.0f, // bottom right back
	//};
	

	GLushort indices[] = {
		0, 1, 2
	};

	getUnitCircleVertices(6, mesh);

	vertices[0] = verts[0];
	vertices[1] = verts[1];
	vertices[2] = verts[2];
	vertices[3] = verts[9];
	vertices[4] = verts[10];
	vertices[5] = verts[11];
	vertices[6] = verts[12];

	vertices[7] = verts[3];
	vertices[8] = verts[4];
	vertices[9] = verts[5];
	vertices[10] = verts[9];
	vertices[11] = verts[10];
	vertices[12] = verts[11];
	vertices[13] = verts[12];

	vertices[14] = verts[6];
	vertices[15] = verts[7];
	vertices[16] = verts[8];
	vertices[17] = verts[9];
	vertices[18] = verts[10];
	vertices[19] = verts[11];
	vertices[20] = verts[12];


	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	//create 2 buffers
	glGenBuffers(2, mesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	mesh.nIndices = std::size(indices);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//tells how many values for a vertex
	const GLuint floatsPerVertex = 3;
	//tells how many values for a color
	const GLuint floatsPerColor = 4;

	//(2 + 4) * 1 = 6 strides
	//tells program that it'll need to hit 6 numbers before starting to draw the
	//next vertex
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);

	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(1);

}

void getUnitCircleVertices(float sectorCount, GLMesh& mesh)
{
	mesh.verts[0] = 1.0f;


	

	//const float PI = 3.1415926f;
	//float sectorStep = 2 * PI / sectorCount;
	//float sectorAngle;  // radian

	//std::vector<float> unitCircleVertices;
	//for (int i = 0; i <= sectorCount; ++i)
	//{
	//	sectorAngle = i * sectorStep;
	//	unitCircleVertices.push_back(cos(sectorAngle)); // x
	//	unitCircleVertices.push_back(sin(sectorAngle)); // y
	//	unitCircleVertices.push_back(0);                // z
	//}
	
}



bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
	//error reporting
	int success = 0;
	char infoLog[512];

	//create shader program object
	programId = glCreateProgram();

	//create vertex and frag shader obj
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	//get shader source
	glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
	glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

	//compile vertex shader
	glCompileShader(vertexShaderId);

	//check for errors
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	//compile frag shader
	glCompileShader(fragmentShaderId);

	//check for errors
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	//shaders compiled, attach to shader program object from above
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	//link the program object
	glLinkProgram(programId);

	//check for linking errors
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		return false;
	}

	glUseProgram(programId);

	return true;
}

void UProcessInput(GLFWwindow* window)
{
	// 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// fill shapes
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// fill lines
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void URender()
{
	// Enable z-depth
	glEnable(GL_DEPTH_TEST);

	//clear background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// scale the object
	glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	glm::mat4 rotation = glm::rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	// move the object (x, y, z)
	glm::mat4 translation = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));


	// model matrix - transformations applies left --> right
	glm::mat4 model = translation * rotation * scale;

	// transform the camera (x, y, z)
	glm::mat4 view = glm::translate(glm::vec3(0.0f, 0.0f, -5.0f));

	// create perspective projection (fov, aspect ratio, near plane, far plane)
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);

	// set shader
	glUseProgram(gShaderProgram);

	// gets and passes transform matrices to shader prgm
	GLint modelLocation = glGetUniformLocation(gShaderProgram, "model");
	GLint viewLocation = glGetUniformLocation(gShaderProgram, "view");
	GLint projLocation = glGetUniformLocation(gShaderProgram, "projection");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));


	// activate vbo's within mesh's vao
	glBindVertexArray(gMesh.vao);

	//draw the triangles
	glDrawElements(GL_TRIANGLES, gMesh.nIndices, GL_UNSIGNED_SHORT,
		NULL);

	// deactivate vao
	glBindVertexArray(0);

	// swap front and back buffers
	glfwSwapBuffers(gWindow);


}

void UResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void UDestroyMesh(GLMesh& mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(2, mesh.vbos);
}

void UDestroyShaderProgram(GLuint programId)
{
	glDeleteProgram(programId);
}


