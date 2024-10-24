#version 430 

out vec4 color;

layout(binding = 0) uniform sampler2D uSampler;

in vec2 posXY;

void main() {
    color = texture(uSampler,posXY);
}