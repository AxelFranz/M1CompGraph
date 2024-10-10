#version 430
precision highp float;

// OUTPUT
out vec4 oFragmentColor;
in vec3 position;
layout(binding = 0) uniform samplerCube uTextureCube;

// MAIN PROGRAM
void main()
{
    oFragmentColor = texture(uTextureCube,position);
}