//---------------------------------------------------
//
// Lawrence Artl | LorenArms
// CS-330 Comp Graphic and Viz
// Assignment 6-3
//
// LIGHTING A PYRAMID
//
//---------------------------------------------------


#include "ShapeBuilder.h"
#include "Mesh.h"
#include "SceneBuilder.h"

// image
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> 


// shader program macros
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif


using namespace std;

//window title
const char* const WINDOW_TITLE = "Module 6 Assignment: Lighting";

//window width, height
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

struct GLightMesh
{
	GLuint vao;         // Handle for the vertex array object
	GLuint vbo;         // Handle for the vertex buffer object
	GLuint nVertices;    // Number of indices of the mesh
};

GLightMesh ambLightMesh;
GLightMesh fillLightMesh;
ShapeBuilder builder;

//main window
GLFWwindow* gWindow = nullptr;

//shader program
GLuint gShaderProgram;
GLuint gLampProgramId;

// scene vector for drawing shapes
vector<GLMesh> scene;

// variable to handle ortho change
bool perspective = false;


// camera
Camera gCamera(glm::vec3(0.0f, 4.0f, 8.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -25.0f);



float gLastX = WINDOW_WIDTH / 2.0f;
float gLastY = WINDOW_HEIGHT / 2.0f;
bool gFirstMouse = true;


// timing
float gDeltaTime = 0.0f; // time between current frame and last frame
float gLastFrame = 0.0f;


// Light color, position and scale
glm::vec3 gAmbLightColor(1.0f, 1.0f, 1.0f);
glm::vec3 gAmbLightPosition(-1.5f, 1.0f, -1.5f);
glm::vec3 gAmbLightScale(0.1f);

// Light color, position and scale
glm::vec3 gFillLightColor(0.0f, 1.0f, 0.0f);
glm::vec3 gFillLightPosition(-1.5f, 3.0f, -1.5f);
glm::vec3 gFillLightScale(0.1f);

bool gIsLampOrbiting = true;

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
void UCreateLightMesh(GLightMesh& lightMesh);





// Shape Vertex Shader Source Code
const GLchar* vertex_shader_source = GLSL(440,
	layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
layout(location = 1) in vec3 normal; // VAP position 1 for normals
layout(location = 2) in vec2 textureCoordinate;

out vec3 vertexNormal; // For outgoing normals to fragment shader
out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
out vec2 vertexTextureCoordinate;

//Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

	vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

	vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
	vertexTextureCoordinate = textureCoordinate;
}
);



// Shape Fragment Shader Source Code
const GLchar* fragment_shader_source = GLSL(440,

	in vec3 vertexFragmentPos;
	in vec3 vertexNormal;	
	in vec2 vertexTextureCoordinate; // for texture coordinates, not color

	out vec4 fragmentColor;
	
	uniform vec3 objectColor;
	uniform vec3 lightColor;
	uniform vec3 fillLightColor;
	uniform vec3 lightPos;
	uniform vec3 fillLightPos;
	uniform vec3 viewPosition;
	
	uniform sampler2D uTexture;
	uniform vec2 uvScale;

void main()
{
	/*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

		//Calculate Ambient lighting*/
	float ambientStrength = 0.1f; // Set ambient or global lighting strength
	vec3 ambient = ambientStrength * lightColor; // Generate ambient light color
	vec3 fill = ambientStrength * fillLightColor;

	//Calculate Diffuse lighting*/
	vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
	vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on cube
	vec3 fillLightDirection = normalize(fillLightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on cube

	float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
	float fillImpact = max(dot(norm, fillLightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light

	vec3 diffuse = impact * lightColor; // Generate diffuse light color
	vec3 fillDiffuse = fillImpact * fillLightColor;

	//Calculate Specular lighting*/
	float specularIntensity = 0.4f; // Set specular light strength
	float highlightSize = 16.0f; // Set specular highlight size
	vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
	vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
	//Calculate specular component
	float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
	vec3 specular = specularIntensity * specularComponent * lightColor;
	vec3 fillSpecular = specularIntensity * specularComponent * fillLightColor;

	// Texture holds the color to be used for all three components
	vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

	// Calculate phong result
	vec3 phong = (ambient + diffuse + fillDiffuse + specular) * textureColor.xyz;

	fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU

}
);






// Light Shader Source Code
const GLchar* lampVertexShaderSource = GLSL(440,

	layout(location = 0) in vec3 position; // VAP position 0 for vertex position data

		//Uniform / Global variables for the  transform matrices
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates
}
);

// Light Fragment Shader Source Code
const GLchar* lampFragmentShaderSource = GLSL(440,

	out vec4 fragmentColor; // For outgoing lamp color (smaller cube) to the GPU

void main()
{
	fragmentColor = vec4(1.0f); // Set color to white (1.0f,1.0f,1.0f) with alpha 1.0
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


	SceneBuilder::UBuildScene(scene);
	
	//build shader 

	for (auto& m : scene)
	{
		if (!UCreateTexture(m.texFilename, m.textureId))
		{
			cout << "Failed to load texture " << m.texFilename << endl;
			return EXIT_FAILURE;

		}

		if (!UCreateShaderProgram(vertex_shader_source, fragment_shader_source,
			gShaderProgram))
			return EXIT_FAILURE;

		
	}

	if (!UCreateShaderProgram(lampVertexShaderSource, lampFragmentShaderSource, gLampProgramId))
		return EXIT_FAILURE;

	// Create Light Object
	UCreateLightMesh(ambLightMesh);
	UCreateLightMesh(fillLightMesh);



	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	glUseProgram(gShaderProgram);
	// We set the texture as texture unit 0
	glUniform1i(glGetUniformLocation(gShaderProgram, "uTexture"), 0);
	
	//rendering loop
	//keep checking if window has closed
	while (!glfwWindowShouldClose(gWindow))
	{
		//bg color of window
		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);


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
	for (auto& m : scene)
	{
		UDestroyMesh(m);
	}

	scene.clear();
	
	UDestroyShaderProgram(gShaderProgram);
	UDestroyShaderProgram(gLampProgramId);

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


	// Move camera
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

	// Modify light position
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		gAmbLightPosition.x -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		gAmbLightPosition.x += 0.005f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		gAmbLightPosition.z -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		gAmbLightPosition.z += 0.005f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		gAmbLightPosition.y -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		gAmbLightPosition.y += 0.005f;


	// Modify light color (1, 2, 3)
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		gFillLightColor.r += 0.001f;
		if (gFillLightColor.r > 1.0f)
		{
			gFillLightColor.r = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		gFillLightColor.g += 0.001f;
		if (gFillLightColor.g > 1.0f)
		{
			gFillLightColor.g = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		gFillLightColor.b += 0.001f;
		if (gFillLightColor.b > 1.0f)
		{
			gFillLightColor.b = 0.0f;
		}
	}



	// Toggle perspective versus ortho view
	// V / B
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		perspective = false;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		perspective = true;

		
	// Pause and resume lamp orbiting
	static bool isLKeyDown = false;
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && !gIsLampOrbiting)
		gIsLampOrbiting = true;
	else if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS && gIsLampOrbiting)
		gIsLampOrbiting = false;


	


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
	const float angularVelocity = glm::radians(45.0f);
	if (gIsLampOrbiting)
	{
		glm::vec4 newPosition = glm::rotate(angularVelocity * gDeltaTime, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(gAmbLightPosition, 5.0f);
		gAmbLightPosition.x = newPosition.x;
		gAmbLightPosition.y = newPosition.y;
		gAmbLightPosition.z = newPosition.z;
	}

	// Enable z-depth
	glEnable(GL_DEPTH_TEST);

	// Background (black)
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

			
	
	// loop to draw each shape individually
	for (auto i = 0; i < scene.size(); ++i)
	{
		auto mesh = scene[i];

		// activate vbo's within mesh's vao
		glBindVertexArray(mesh.vao);

		// set shader
		glUseProgram(gShaderProgram);
		
		// gets and passes transform matrices to shader prgm
		GLint modelLocation = glGetUniformLocation(gShaderProgram, "model");
		GLint viewLocation = glGetUniformLocation(gShaderProgram, "view");
		GLint projLocation = glGetUniformLocation(gShaderProgram, "projection");

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mesh.model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

		// Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
		GLint objectColorLoc = glGetUniformLocation(gShaderProgram, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(gShaderProgram, "lightColor");
		GLint fillLightColorLoc = glGetUniformLocation(gShaderProgram, "fillLightColor");

		GLint lightPositionLoc = glGetUniformLocation(gShaderProgram, "lightPos");
		GLint fillLightPositionLoc = glGetUniformLocation(gShaderProgram, "fillLightPos");

		GLint viewPositionLoc = glGetUniformLocation(gShaderProgram, "viewPosition");


		// Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
		glUniform3f(objectColorLoc, mesh.p[0], mesh.p[1], mesh.p[2]);

		glUniform3f(lightColorLoc, gAmbLightColor.r, gAmbLightColor.g, gAmbLightColor.b);
		glUniform3f(lightPositionLoc, gAmbLightPosition.x, gAmbLightPosition.y, gAmbLightPosition.z);

		glUniform3f(fillLightColorLoc, gFillLightColor.r, gFillLightColor.g, gFillLightColor.b);
		glUniform3f(fillLightPositionLoc, gFillLightPosition.x, gFillLightPosition.y, gFillLightPosition.z);

		const glm::vec3 cameraPosition = gCamera.Position;
		glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
		

		GLint UVScaleLoc = glGetUniformLocation(gShaderProgram, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(mesh.gUVScale));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.textureId);

		// Draws the triangles
		glDrawArrays(GL_TRIANGLES, 0, mesh.nIndices);
		
		
	}
	
	
	// Draw the light
	glUseProgram(gLampProgramId);

	glBindVertexArray(ambLightMesh.vao);

	// Light location and Scale
	glm::mat4 model = glm::translate(gAmbLightPosition) * glm::scale(gAmbLightScale);
	
	// Matrix uniforms from the Lamp Shader program
	GLint modelLoc = glGetUniformLocation(gLampProgramId, "model");
	GLint viewLoc = glGetUniformLocation(gLampProgramId, "view");
	GLint projLoc = glGetUniformLocation(gLampProgramId, "projection");

	// Matrix data
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, ambLightMesh.nVertices);



	// Draw the light
	glUseProgram(gLampProgramId);

	glBindVertexArray(fillLightMesh.vao);

	// Light location and Scale
	model = glm::translate(gFillLightPosition) * glm::scale(gFillLightScale);

	// Matrix uniforms from the Lamp Shader program
	modelLoc = glGetUniformLocation(gLampProgramId, "model");
	viewLoc = glGetUniformLocation(gLampProgramId, "view");
	projLoc = glGetUniformLocation(gLampProgramId, "projection");

	// Matrix data
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, fillLightMesh.nVertices);





		
	// deactivate vao's
	glBindVertexArray(0);
	glUseProgram(0);
	
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





// Implements the UCreateMesh function
void UCreateLightMesh(GLightMesh& lightMesh)
{
	// Position and Color data
	GLfloat verts[] = {
		//Positions          //Normals
		// ------------------------------------------------------
		//Back Face          //Negative Z Normal  Texture Coords.
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	   //Front Face         //Positive Z Normal
	  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

	  //Left Face          //Negative X Normal
	 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 //Right Face         //Positive X Normal
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 //Bottom Face        //Negative Y Normal
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	//Top Face           //Positive Y Normal
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerNormal = 3;
	const GLuint floatsPerUV = 2;

	lightMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

	glGenVertexArrays(1, &lightMesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(lightMesh.vao);

	// Create 2 buffers: first one for the vertex data; second one for the indices
	glGenBuffers(1, &lightMesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, lightMesh.vbo); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	// Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
	glEnableVertexAttribArray(2);
}