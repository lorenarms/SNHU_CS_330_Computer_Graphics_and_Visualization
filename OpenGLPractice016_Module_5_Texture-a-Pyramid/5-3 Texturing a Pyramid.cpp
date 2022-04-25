//---------------------------------------------------
//
// Lawrence Artl
// CS-330 Comp Graphic and Viz
// Assignment 5-3
//
// TEXTURING A PYRAMID
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

// camera
#include <camera.h>

// image
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> 



// shader program macros
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif


using namespace std;

//window title
const char* const WINDOW_TITLE = "Module 5 Assignment: Texture a Pyramid";

//window width, height
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//GL data for mesh
struct GLMesh
{
	//vertex array
	GLuint vao;
	//vertex buffer
	GLuint vbo;
	//indices of the mesh
	GLuint nIndices;

	// each shape gets a matrix object
	glm::mat4 scale;
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::mat4 model;
	glm::vec2 gUVScale;

	GLuint textureId;
	
	GLint gTextWrapMode = GL_REPEAT;
	//texture wrapping mode: repeat texture
	//also can use:
	//GLint gTextWrapMode = GL_MIRRORED_REPEAT;
	//GLint gTextWrapMode = GL_CLAMP_TO_EDGE;
	//GLint gTextWrapMode = GL_CLAMP_TO_BORDER;

};



//main window
GLFWwindow* gWindow = nullptr;

//shader program
GLuint gShaderProgram;

// scene vector for drawing shapes
vector<GLMesh> scene;

// variable to handle ortho change
bool perspective = false;


// camera
Camera gCamera(glm::vec3(0.0f, 1.5f, 5.0f));
float gLastX = WINDOW_WIDTH / 2.0f;
float gLastY = WINDOW_HEIGHT / 2.0f;
bool gFirstMouse = true;


// timing
float gDeltaTime = 0.0f; // time between current frame and last frame
float gLastFrame = 0.0f;



//initialize program
bool UInitialize(int, char* [], GLFWwindow** window);
//set window size
void UResizeWindow(GLFWwindow* window, int width, int height);
//process user input
void UProcessInput(GLFWwindow* window);
//render graphics
void URender(vector<GLMesh> scene);
//compile shaders
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource,
	GLuint& programId);
//free up memory on close
void UDestroyMesh(GLMesh& mesh);
void UDestroyShaderProgram(GLuint programId);
void UDestroyTexture(GLuint textureId);

// build shapes
void UBuildPyramid(GLMesh& mesh, vector<float> properties);
void UBuildCylinder(GLMesh& mesh, vector<float> properties, float radius, float length);
void UBuildCone(GLMesh& mesh, vector<float> properties, float radius, float length);
void UBuildPlane(GLMesh& mesh, vector<float> properties);
void UBuildCircle(GLMesh& mesh, vector<float> properties, float radius);


// keyboard and mouse input functions
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

// texture create
bool UCreateTexture(const char* filename, GLuint& textureId);



// Vertex Shader Source Code
const GLchar* vertex_shader_source = GLSL(440,
	layout(location = 0) in vec3 position; // Vertex data from Vertex Attrib Pointer 0
layout(location = 2) in vec2 textureCoordinate;  // Color data from Vertex Attrib Pointer 1

out vec2 vertexTextureCoordinate; // variable to transfer color data to the fragment shader

//uniform mat4 shaderTransform; // 4x4 matrix variable for transforming vertex data
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f); // transforms vertices to clip coordinates
	vertexTextureCoordinate = textureCoordinate;
}
);

// Fragment Shader Source Code
const GLchar* fragment_shader_source = GLSL(440,
	in vec2 vertexTextureCoordinate; // for texture coordinates, not color

out vec4 fragmentColor;

uniform sampler2D uTexture;
uniform vec2 uvScale;

void main()
{
	fragmentColor = texture(uTexture, vertexTextureCoordinate * uvScale);
}
);

void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
	for (int j = 0; j < height / 2; ++j)
	{
		int index1 = j * width * channels;
		int index2 = (height - 1 - j) * width * channels;

		for (int i = width * channels; i > 0; --i)
		{
			unsigned char tmp = image[index1];
			image[index1] = image[index2];
			image[index2] = tmp;
			++index1;
			++index2;
		}
	}
}



//main
int main(int argc, char* argv[])
{
	//check if initialized correctly
	if (!UInitialize(argc, argv, &gWindow))
		return EXIT_FAILURE;

	// build shape meshes
	// build pyramid
	GLMesh gMesh01;
	vector<float> properties = {
		 0.5f,  0.0f,  0.8f,  1.0f,
		 2.0f,  2.0f,  2.0f,
		 0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  1.0f,  -2.0
	};
	// build shape
	UBuildPyramid(gMesh01, properties);

	/*GLMesh gMesh02;
	properties = {
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f
	};
	UBuildCone(gMesh02, properties, 1.0f, 1.0f);*/


	// add shape to scene vector
	

	//build shader programs
	if (!UCreateShaderProgram(vertex_shader_source, fragment_shader_source,
		gShaderProgram))
		return EXIT_FAILURE;

	const char* texFilename = "bricks.png";

	if (!UCreateTexture(texFilename, gMesh01.textureId))
	{
		cout << "Failed to load texture " << texFilename << endl;
		return EXIT_FAILURE;
	}

	if (!UCreateShaderProgram(vertex_shader_source, fragment_shader_source,
		gShaderProgram))
		return EXIT_FAILURE;

	texFilename = "smiley.png";

	/*if (!UCreateTexture(texFilename, gMesh02.textureId))
	{
		cout << "Failed to load texture " << texFilename << endl;
		return EXIT_FAILURE;
	}*/

	scene.push_back(gMesh01);
	//scene.push_back(gMesh02);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	glUseProgram(gShaderProgram);
	// We set the texture as texture unit 0
	glUniform1i(glGetUniformLocation(gShaderProgram, "uTexture"), 0);

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


	//clean up
	scene.clear();
	properties.clear();

	UDestroyMesh(gMesh01);


	UDestroyShaderProgram(gShaderProgram);

	//exit with success!
	exit(EXIT_SUCCESS);

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



	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		gCamera.ProcessKeyboard(LEFT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		gCamera.ProcessKeyboard(UP, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
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


	// deprecated way to change speed of camera
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
	// change camera speed by mouse scroll
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
		// p for perspective (default)
		projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	}
	else
		// o for ortho
		projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);


	// set shader
	glUseProgram(gShaderProgram);

	// gets and passes transform matrices to shader prgm
	GLint modelLocation = glGetUniformLocation(gShaderProgram, "model");
	GLint viewLocation = glGetUniformLocation(gShaderProgram, "view");
	GLint projLocation = glGetUniformLocation(gShaderProgram, "projection");

	// loop to draw each shape individually
	for (auto i = 0; i < scene.size(); ++i)
	{
		auto mesh = scene[i];

		

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mesh.model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

		GLint UVScaleLoc = glGetUniformLocation(gShaderProgram, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(mesh.gUVScale));

		// activate vbo's within mesh's vao
		glBindVertexArray(mesh.vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.textureId);

		// Draws the triangles
		glDrawArrays(GL_TRIANGLES, 0, mesh.nIndices);
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
	glDeleteBuffers(1, &mesh.vbo);
}
void UDestroyShaderProgram(GLuint programId)
{
	glDeleteProgram(programId);
}


// shape builders
//void UBuildPyramid(GLMesh& mesh, vector<float> properties)
//{
//
//	//coordinates and colors for triangles
//	//normalized to window
//	// Specifies normalized device coordinates (x,y,z) and color for square vertices
//	GLfloat verts[] =
//	{
//		// Vertex Positions    // Colors
//		 0.0f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f, 1.0f, // top of pyramid, red
//		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f, // bottom left front
//		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, 1.0f, // bottom right front
//
//		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f, 1.0f, // bottom left back
//		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f, 1.0f, // bottom right back
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
//		if(step == 2)
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
//	vert*=2;
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
//
//	glGenVertexArrays(1, &mesh.vao);
//	glBindVertexArray(mesh.vao);
//
//	//create 2 buffers
//	glGenBuffers(2, mesh.vbos);
//	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
//
//	
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
//	 //build the top of the cylinder
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


void UBuildPyramid(GLMesh& mesh, vector<float> properties)
{

	//coordinates and colors for triangles
	//normalized to window
	// Specifies normalized device coordinates (x,y,z) and color for square vertices
	GLfloat verts[] =
	{
		// Vertex Positions    // Texture coords
		 0.0f,  0.7f,  0.0f,	0.5f, 1.0f,		//back side
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,	1.0f, 0.0f,

		 0.0f,  0.7f,  0.0f,	0.5f, 1.0f,		//left side
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,	1.0f, 0.0f,

		 0.0f,  0.7f,  0.0f,	0.5f, 1.0f,		//front
		-1.0f, -1.0f,  1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,	1.0f, 0.0f,

		 0.0f,  0.7f,  0.0f,	0.5f, 1.0f,		//right side
		 1.0f, -1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,	1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		//bottom back
		 1.0f, -1.0f, -1.0f,	1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,	0.0f, 0.0f,

		 1.0f, -1.0f, -1.0f,	1.0f, 1.0f,		//bottom front
		-1.0f, -1.0f,  1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,	0.0f, 1.0f,
	};

	

	

	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerUV = 2;

	mesh.nIndices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerUV));

	glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(mesh.vao);

	// Create VBO
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	// Strides between vertex coordinates
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV);

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(2);

	//***************************************


	// scale the object
	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale;\

	mesh.gUVScale = glm::vec2(3.0f, 3.0f);		// use this to scale the texture to be larger

}
void UBuildCircle(GLMesh& mesh, vector<float> properties, float radius) {
	vector<float> v;

	const float PI = 3.14f;
	const float STEP = 24;
	float sectorStep = 2.0f * PI / STEP;

	for (int i = 0; i < STEP; i++) {

		v.push_back(0.0f); v.push_back(0.0f); v.push_back(0.0f);    // coords
		v.push_back(0.0f); v.push_back(0.0f);   // text

		v.push_back(radius * cos(i * sectorStep));    // x
		v.push_back(radius * sin(i * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(0.0f);   // text

		v.push_back(radius * cos((i + 1) * sectorStep));    // x
		v.push_back(radius * sin((i + 1) * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(1.0f);   // text
	}

	GLfloat verts[370];

	for (int i = 0; i < v.size(); i++)
	{
		verts[i] = v[i];
	}



	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerUV = 2;

	mesh.nIndices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerUV));

	glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(mesh.vao);

	// Create VBO
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	// Strides between vertex coordinates
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV);

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(2);

	//***************************************


		// scale the object
	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale;

	mesh.gUVScale = glm::vec2(1.0f, 1.0f);
}


void UBuildCone(GLMesh& mesh, vector<float> properties, float radius, float length)
{
	// this is the same algorithm as the cylinder
	// i plain run out of time to tweak it :(
	// so it's a little rough and big on memory

	

	//int i = 0;
	//GLfloat verts[]
	//{
	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(1 * sectorStep), radius* sin(1 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(2 * sectorStep), radius* sin(2 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(2 * sectorStep), radius* sin(2 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(3 * sectorStep), radius* sin(3 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(3 * sectorStep), radius* sin(3 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(4 * sectorStep), radius* sin(4 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(4 * sectorStep), radius* sin(4 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(5 * sectorStep), radius* sin(5 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(5 * sectorStep), radius* sin(5 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(6 * sectorStep), radius* sin(6 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(6 * sectorStep), radius* sin(6 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(7 * sectorStep), radius* sin(7 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(7 * sectorStep), radius* sin(7 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(8 * sectorStep), radius* sin(8 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(8 * sectorStep), radius* sin(8 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(9 * sectorStep), radius* sin(9 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(9 * sectorStep), radius* sin(9 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(10 * sectorStep), radius* sin(10 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(10 * sectorStep), radius* sin(10 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(11 * sectorStep), radius* sin(11 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(11 * sectorStep), radius* sin(11 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(12 * sectorStep), radius* sin(12 * sectorStep), 0.0f, 1.0f, 1.0f,

	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	radius* cos(12 * sectorStep), radius* sin(12 * sectorStep), 0.0f, 1.0f, 0.0f,
	//	radius* cos(1 * sectorStep), radius* sin(1 * sectorStep), 0.0f, 1.0f, 1.0f,


	//	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// top origin
	//	0.0f, 1.0f, 0.0f, 2.0f, 0.0f,			// top origin
	//	0.0f, 0.0f, 1.0f, 2.0f, 2.0f			// top origin



	//};

	const float PI = 3.14f;
	const float STEP = 12;
	float sectorStep = 2.0f * PI / STEP;

	vector<float> v;
	
	for (int i = 1; i < STEP; i++) {

		// triangle top, fan
		// point 1
		v.push_back(0.0f); v.push_back(0.0f); v.push_back(0.0f);    // center coords
		v.push_back(0.0f); v.push_back(0.0f);   // text

		// point 2
		v.push_back(radius * cos(i * sectorStep));    // x
		v.push_back(radius * sin(i * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(0.0f);   // text

		//point 3
		v.push_back(radius * cos((i + 1) * sectorStep));    // x
		v.push_back(radius * sin((i + 1) * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(1.0f);   // text


		// side triangle
		// point 1
		v.push_back(radius * cos((i + 1) * sectorStep));    // x
		v.push_back(radius * sin((i + 1) * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(1.0f);   // text

		// point 2, point of cone
		v.push_back(0.0f); v.push_back(0.0f); v.push_back(length);    // center coords
		v.push_back(0.0f); v.push_back(0.0f);   // text

		// point 3
		v.push_back(radius * cos(i * sectorStep));    // x
		v.push_back(radius * sin(i * sectorStep));    // y
		v.push_back(0.0f);                          // z
		v.push_back(1.0f); v.push_back(0.0f);   // text

		// ADD IN LOGIC TO HAVE LAST TRIANGLE AND SIDE WRITTEN

	}

	

	GLfloat verts[370];

	for (int i = 0; i < v.size(); i++)
	{
		verts[i] = v[i];
	}

	

const GLuint floatsPerVertex = 3;
const GLuint floatsPerUV = 2;

mesh.nIndices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerUV));

glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
glBindVertexArray(mesh.vao);

// Create VBO
glGenBuffers(1, &mesh.vbo);
glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

// Strides between vertex coordinates
GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV);

// Create Vertex Attribute Pointers
glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
glEnableVertexAttribArray(0);

glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float)* floatsPerVertex));
glEnableVertexAttribArray(2);

//***************************************


	// scale the object
	mesh.scale = glm::scale(glm::vec3(properties[4], properties[5], properties[6]));

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.rotation = glm::rotate(properties[7], glm::vec3(properties[8], properties[9], properties[10]));

	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(properties[11], properties[12], properties[13]));

	mesh.model = mesh.translation * mesh.rotation * mesh.scale;

	mesh.gUVScale = glm::vec2(1.0f, 1.0f);
}

bool UCreateTexture(const char* filename, GLuint& textureId)
{
	int width, height, channels;
	unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
	if (image)
	{
		flipImageVertically(image, width, height, channels);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (channels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		else if (channels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		else
		{
			cout << "Not implemented to handle image with " << channels << " channels" << endl;
			return false;
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

		return true;
	}

	// Error loading the image
	return false;
}

void UDestroyTexture(GLuint textureId)
{
	glGenTextures(1, &textureId);
}