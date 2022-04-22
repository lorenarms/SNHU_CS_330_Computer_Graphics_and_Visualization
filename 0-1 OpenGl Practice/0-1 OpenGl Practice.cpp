

#include <iostream>


#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <camera.h>

// shader program macros
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif


using namespace std;

//window title
const char* const WINDOW_TITLE = "Module 3 Assignment: 3D Scene";








// variables and methods
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


	glm::mat4 scale;
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::mat4 model;

};

// camera
Camera gCamera(glm::vec3(0.0f, 0.0f, 5.0f));
float gLastX = WINDOW_WIDTH / 2.0f;
float gLastY = WINDOW_HEIGHT / 2.0f;
bool gFirstMouse = true;

// timing
float gDeltaTime = 0.0f; // time between current frame and last frame
float gLastFrame = 0.0f;

GLFWwindow* gWindow = nullptr;		//main window

GLuint gShaderProgram;				//shader program

vector<GLMesh> scene;				// scene vector for drawing shapes
bool perspective = false;			//is the image in perspective or ortho mode

bool UInitialize(int, char* [], GLFWwindow** window);				//initialize program			
void UResizeWindow(GLFWwindow* window, int width, int height);		//set window size
void UProcessInput(GLFWwindow* window);								//process user input
void URender(vector<GLMesh> scene);									//render graphics
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource,
	GLuint& programId);				//compile shaders
void UDestroyMesh(GLMesh& mesh);	//free up memory on close
void UDestroyShaderProgram(GLuint programId);

// keyboard and mouse input functions
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

// shape builders
void UBuildTriangle(GLMesh& mesh, vector<float> properties);
void UBuildTriangleFan(GLMesh& mesh, vector<float> properties);









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








// main method and game loop
int main(int argc, char* argv[])
{

	//check if initialized correctly
	if (!UInitialize(argc, argv, &gWindow))
		return EXIT_FAILURE;

	// build shape meshes
	GLMesh gMesh01;

	
	vector<float> properties = {
		 0.0f,  0.0f,  0.0f,  0.0f,
		 2.0f,  2.0f,  2.0f,
		 0.0f,  2.0f,  0.0f,  0.0f,
		 0.0f,  0.0f,  0.0f
	};
	UBuildTriangle(gMesh01, properties);
	scene.push_back(gMesh01);

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
		float currentFrame = glfwGetTime();
		gDeltaTime = currentFrame - gLastFrame;
		gLastFrame = currentFrame;

		//process user input
		UProcessInput(gWindow);

		//render frame
		URender(scene);
		
		glfwPollEvents();
	}

    return 0;
}




// functions
// initialize and build shaders
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
	glfwSetCursorPosCallback(*window, UMousePositionCallback);
	glfwSetScrollCallback(*window, UMouseScrollCallback);
	glfwSetMouseButtonCallback(*window, UMouseButtonCallback);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

// process user input and windows changes
void UProcessInput(GLFWwindow* window)
{

	// exit program
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// draw lines
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// fill shapes
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	//
	// key presses for movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		gCamera.ProcessKeyboard(LEFT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		gCamera.ProcessKeyboard(UP, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		gCamera.ProcessKeyboard(DOWN, gDeltaTime);


	// I originally had this as a single key (P) toggle, but the key press registers
	// so quickly that it took several presses to get it to land on the desired output
	// separating the statement allowed me to toggle when I wanted
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		perspective = false;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		perspective = true;

	// original statement below 
	/*if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		if (!perspective)
		{
			perspective = true;
		}
		else
			perspective = false;
	}*/


	// change speed of camera with z and x keys
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		if (gCamera.MovementSpeed < 10.0f)
		{
			gCamera.MovementSpeed += 0.01f;
		}
		else
			gCamera.MovementSpeed = 10.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		if (gCamera.MovementSpeed > 0.01f)
		{
			gCamera.MovementSpeed -= 0.01f;
		}
		else
			gCamera.MovementSpeed = 0.01f;
	}

}
void UResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (gFirstMouse)
	{
		gLastX = xpos;
		gLastY = ypos;
		gFirstMouse = false;
	}

	float xoffset = xpos - gLastX;
	float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

	gLastX = xpos;
	gLastY = ypos;

	gCamera.ProcessMouseMovement(xoffset, yoffset);
}
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	// change camera speed with mouse scroll

	gCamera.ProcessMouseScroll(yoffset);
}
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		if (action == GLFW_PRESS)
			cout << "LP" << endl;
		else
			cout << "LR" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
	{
		if (action == GLFW_PRESS)
			cout << "MP" << endl;
		else
			cout << "MR" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_RIGHT:
	{
		if (action == GLFW_PRESS)
			cout << "RP" << endl;
		else
			cout << "RR" << endl;
	}
	break;

	default:
		cout << "Unhandled mouse button event" << endl;
		break;
	}
}

// render the scene
void URender(vector<GLMesh> scene)
{
	// Enable z-depth
	glEnable(GL_DEPTH_TEST);

	//clear background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// transform the camera (x, y, z)
	glm::mat4 view = gCamera.GetViewMatrix();

	// create perspective projection (fov, aspect ratio, near plane, far plane)
	glm::mat4 projection;
	if (!perspective)
	{
		projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	}
	else
		projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);


	// set shader
	glUseProgram(gShaderProgram);

	// gets and passes transform matrices to shader prgm
	GLint modelLocation = glGetUniformLocation(gShaderProgram, "model");
	GLint viewLocation = glGetUniformLocation(gShaderProgram, "view");
	GLint projLocation = glGetUniformLocation(gShaderProgram, "projection");

	// loop for each shape, draw
	for (auto i = 0; i < scene.size(); ++i)
	{
		auto mesh = scene[i];

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mesh.model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

		// activate vbo's within mesh's vao
		glBindVertexArray(mesh.vao);

		//draw the triangles
		glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL);

	}

	// deactivate vao
	glBindVertexArray(0);

	// swap front and back buffers
	glfwSwapBuffers(gWindow);

}

// clean-up methods
void UDestroyMesh(GLMesh& mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(2, mesh.vbos);
}
void UDestroyShaderProgram(GLuint programId)
{
	glDeleteProgram(programId);
}

// shape builder methods
void UBuildTriangle(GLMesh& mesh, vector<float> properties)
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
		-1.0f, 0.0f, 0.0f,		//top left t, lower left v
		1.0f, 0.5f, 0.0f, 1.0f, //red

		//index 2
		-1.0f, 1.0f, 0.0f,		//top left t, upper left v
		1.0f, 1.0f, 0.0f, 1.0f, //red

		//index 3
		0.0f, 0.0f, 0.0f,		//top right t, lower left v
		0.0f, 0.0f, 1.0f, 1.0f, //blue

		//index 4
		0.0f, 1.0f, 0.0f,		//top right t, upper left v
		0.0f, 0.5f, 1.0f, 1.0f, //blue

		//index 5
		1.0f, 1.0f, 0.0f,		//top right t, upper right v
		0.0f, 1.0f, 1.0f, 1.0f, //blue

		//index 6
		0.0f, 0.0f, 0.0f,		//lower right t, upper left v
		0.0f, 1.0f, 0.0f, 1.0f, //green

		//index 7
		1.0f, 0.0f, 0.0f,		//lower right t, lower left v
		0.0f, 1.0f, 0.5f, 1.0f, //green

		//index 8
		1.0f, -1.0f, 0.0f,		//lower right t, upper right v
		0.0f, 1.0f, 1.0f, 1.0f, //green

		//index 9
		0.0f, 0.0f, 0.0f,		//lower left t, upper right v
		1.0f, 0.0f, 0.8f, 1.0f,	//purple?

		//index 10
		0.0f, -1.0f, 0.0f,		//lower left t, lower right v
		0.7f, 0.0f, 0.8f, 1.0f,	//purple?

		//index 11
		-1.0f, -1.0f, 0.0f,		//lower left t, lower left v
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

	// scale the object
	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale;
}
void UBuildTriangleFan(GLMesh& mesh, vector<float> properties)
{
	
}