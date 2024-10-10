#version 430

// INPUT
layout(location=1) in vec3 position_in;

// UNIFORM
layout(location=0) uniform mat4 model;
layout(location=1) uniform mat4 view;
layout(location=2) uniform mat4 proj;
out vec3 position;

// MAIN PROGRAM
void main()
{
    position = position_in;
    vec4 pos4 = proj*view*model*vec4(position_in,1.f);
    pos4.z=pos4[3];
    gl_Position = pos4;
}