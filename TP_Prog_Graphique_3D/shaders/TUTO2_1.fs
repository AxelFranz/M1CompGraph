#version 430
precision highp float;

// INPUT
in vec3 Colors;

// OUTPUT
out vec4 oFragmentColor;

// MAIN PROGRAM
void main()
{
	oFragmentColor = vec4(Colors, 1.f);
}