#version 430

// INPUT
// - the currently bounded vertex array (VAO) contains a VBO of 2D data (positions)
// - variable is prefixed by "in"
// - its "location index" MUST be the same value when using vertexAttribPointer() and enableVertexAttribArray() during VAO definition
layout(location = 1) in vec2 position_in;
layout(location = 2) uniform float size;
layout(location = 3) uniform mat4 model;
out vec2 position_out;

// MAIN PROGRAM
void main()
{
	// "gl_PointSize" is a predined variable in GLSL to fix the size of primitives of type "GL_POINTS"
	// it wiil be used by the "rasterizer" to generate points of given size in "pixels"
	gl_PointSize = 20.f * 2 * (cos(size)+1) + 10.f;

	// MANDATORY
	// - a vertex shader MUST write the value of the predefined variable " (GLSL langage)"
	// - this value represent a position in NDC space (normalized device coordintes), i.e the cube [-1.0;1.0]x[-1;1.0]x[-1;1.0]
	// gl_Position = vec4(position_in, 0.0, 1.0);
	gl_Position = model*vec4(position_in, 0.0, 1.0);
	position_out = position_in;
}