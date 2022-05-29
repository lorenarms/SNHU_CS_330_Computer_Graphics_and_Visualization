#version 330 core
	layout(location = 0) in vec3 position; // Vertex data from Vertex Attrib Pointer 0
	layout(location = 1) in vec3 color;
	layout(location = 2) in vec2 textureCoordinate;  // Color data from Vertex Attrib Pointer 1

	out vec3 shapeColor;
	out vec2 vertexTextureCoordinate; // variable to transfer color data to the fragment shader

//uniform mat4 shaderTransform; // 4x4 matrix variable for transforming vertex data
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f); // transforms vertices to clip coordinates
	shapeColor = color;
	vertexTextureCoordinate = textureCoordinate;
}
