#version 430
precision highp float;

// OUTPUT
// - the default GL framebuffer is a RGBA color buffer
// - you can choose whatever name you want
// - variable is prefixed by "out"
out vec4 oFragmentColor;
in vec2 position_out;
layout(location = 1) uniform vec3 color;

// MAIN PROGRAM
void main()
{
	// MANDATORY
	// - a fragment shader MUST write an RGBA color
	oFragmentColor = vec4(
		mix(color.x ,position_out.x,0.5f), 
		mix(color.y ,position_out.y,0.5f), 
		color.z , 
		1.f); // [values are between 0.0 and 1.0]
}