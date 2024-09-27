#version 430

// INPUT
layout(location=1) in vec3 position_in;

// UNIFORM
layout(location=2) uniform mat4 model;
layout(location=3) uniform mat4 view;
layout(location=4) uniform mat4 proj;

// MAIN PROGRAM
void main()
{
    gl_PointSize = 1.f;

    gl_Position = proj*view*model*vec4(position_in,1.f);
}