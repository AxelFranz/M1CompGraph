#version 430

layout(location = 1) in vec3 position_in;
layout(location = 2) in vec2 positionUV;
layout(location = 0) uniform mat4 uModelMatrix;
layout(location = 1) uniform mat4 uViewMatrix;
layout(location = 2) uniform mat4 uProjectionMatrix;

out vec2 posXY;

void main() {
    posXY = positionUV;
    vec4 posXYZ = uProjectionMatrix*uViewMatrix*uModelMatrix*vec4(position_in,1.0f);
    gl_Position = posXYZ;
}