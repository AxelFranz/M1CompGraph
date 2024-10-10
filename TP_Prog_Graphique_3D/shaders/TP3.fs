#version 430
precision highp float;

out vec4 oFragmentColor;

layout(location = 4) uniform vec4 uColorMap[255];
layout(binding = 0) uniform sampler2D uSampler;

in vec2 uv;
in float height;

// MAIN PROGRAM
void main()
{
	// MANDATORY
	// - a fragment shader MUST write an RGBA color
	int index = int(height*4*255);
	oFragmentColor = uColorMap[index];
}