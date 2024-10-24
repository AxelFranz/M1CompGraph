#version 430 
precision highp float;

layout (location = 4) uniform vec3 uAlbedo;

layout (location = 0) out vec3 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec3 albedo;
layout (location = 3) out vec3 uKs;

in vec3 v_position;
in vec3 v_normal;

void main() {
    position = v_position;
    normal = normalize(v_normal);
    albedo = uAlbedo;
    uKs = vec3(v_position.x,v_normal.y,v_normal.z);
}