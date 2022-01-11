


//---------------------------------------------------
//
// Lawrence Artl
// CS-330 Comp Graphic and Viz
// Assignment 3-3
//
// **RUN IN x86 MODE
//
//---------------------------------------------------



#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

//window title
const char* const WINDOW_TITLE = "Module 3 Assignment: Pyramid";

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
void UCreateMesh(GLMesh& mesh);
void URender();
//compile shaders
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource,
	GLuint& programId);
//free up memory on close
void UDestroyMesh(GLMesh& mesh);
void UDestroyShaderProgram(GLuint programId);

//shaders
//vertex shader program (location)
const char *vertex_shader_source = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"layout (location=1) in vec4 colorFromVBO;\n"
"out vec4 colorFromVS;\n"
"void main()\n"
"{\n"
"	gl_Position=vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	colorFromVS=colorFromVBO;\n"
"}\n\0";

//frag shader program (color)
const char *fragment_shader_source = "#version 330 core\n"
"in vec4 colorFromVS;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = colorFromVS;\n"
"}\n\0";

//main
int main(int argc, char* argv[])
{
	//check if initialized correctly
	if (!UInitialize(argc, argv, &gWindow))
		return EXIT_FAILURE;

	//create mesh, create vbo
	UCreateMesh(gMesh);

	//build shader programs
	if (!UCreateShaderProgram(vertex_shader_source, fragment_shader_source, 
		gShaderProgram))
		return EXIT_FAILURE;

	//bg color of window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//rendering loop
	//keep checking if window has closed
	while(!glfwWindowShouldClose(gWindow))
	{
		//process user input
		UProcessInput(gWindow);

		//render fram
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

void UCreateMesh(GLMesh& mesh)
{
	//coordinates and colors for triangles
	//normalized to window
	// was supposed to make two triangles
	// wanted a challenge, hope it's okay that I made four
	GLfloat verts[] = {
		//index 0
		0.0f, 0.0f, 0.0f,		//top left t, lower right v
		1.0f, 0.0f, 0.0f, 1.0f, //red

		//index 1
		-0.8f, 0.0f, 0.0f,		//top left t, lower left v
		1.0f, 0.5f, 0.0f, 1.0f, //red

		//index 2
		-0.8f, 0.8f, 0.0f,		//top left t, upper left v
		1.0f, 1.0f, 0.0f, 1.0f, //red

		//index 3
		0.0f, 0.0f, 0.0f,		//top right t, lower left v
		0.0f, 0.0f, 1.0f, 1.0f, //blue

		//index 4
		0.0f, 0.8f, 0.0f,		//top right t, upper left v
		0.0f, 0.5f, 1.0f, 1.0f, //blue

		//index 5
		0.8f, 0.8f, 0.0f,		//top right t, upper right v
		0.0f, 1.0f, 1.0f, 1.0f, //blue

		//index 6
		0.0f, 0.0f, 0.0f,		//lower right t, upper left v
		0.0f, 1.0f, 0.0f, 1.0f, //green

		//index 7
		0.8f, 0.0f, 0.0f,		//lower right t, lower left v
		0.0f, 1.0f, 0.5f, 1.0f, //green

		//index 8
		0.8f, -0.8f, 0.0f,		//lower right t, upper right v
		0.0f, 1.0f, 1.0f, 1.0f, //green

		//index 9
		0.0f, 0.0f, 0.0f,		//lower left t, upper right v
		1.0f, 0.0f, 0.8f, 1.0f,	//purple?

		//index 10
		0.0f, -0.8f, 0.0f,		//lower left t, lower right v
		0.7f, 0.0f, 0.8f, 1.0f,	//purple?

		//index 11
		-0.8f, -0.8f, 0.0f,		//lower left t, lower left v
		0.8f, 0.8f, 0.8f, 1.0f,	//purple?
	};

	const GLushort indices[] = {  
		// triangles share a vertex, but its dif colors for each, so re-render
		0, 1, 2,	//red triangle
		3, 4, 5,	//blue triangle
		6, 7, 8,	//green triangle
		9, 10, 11,	//purple triangle
	};

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	//create 2 buffers
	glGenBuffers(2, mesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

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
	//clear background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(gShaderProgram);

	glBindVertexArray(gMesh.vao);

	glDrawElements(GL_TRIANGLES, gMesh.nIndices, GL_UNSIGNED_SHORT, 
		NULL);

	glBindVertexArray(0);

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


