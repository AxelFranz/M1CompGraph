#version 430
precision highp float;

#define M_PI 3.14159265358979

// INPUT
in vec3 v_norm;
in vec3 v_pos;
in float height;

// OUTPUT
out vec4 oFragmentColor;

// UNIFORM

layout(location=15) uniform vec3  uLightPos;
layout(location=16) uniform float uLightIntensity;


// MAIN PROGRAM
void main()
{
    const vec3 gravelColor = vec3(0.29, 0.24, 0.22);
    const vec3 dirtColor = vec3(0.45, 0.34, 0.19);
    const vec3 grassColor = vec3(0.22, 0.63, 0.28);
    const vec3 rockColor = vec3(0.33, 0.31, 0.31);
    const vec3 snowColor = vec3(0.90, 0.90, 0.95);


    vec3 gravelDirt = mix(gravelColor, dirtColor, smoothstep(-0.5, 0.02, height));
    vec3 dirtGrass = mix(gravelDirt, grassColor, smoothstep(0.03, 0.06, height));
    vec3 grassRock = mix(dirtGrass, rockColor, smoothstep(0.09, 0.10, height));
    vec3 rockSnow = mix(grassRock, snowColor, smoothstep(0.14, 0.15, height));
    vec3 Kd = rockSnow.rgb;

    vec3 normal = normalize(v_norm);
    if (gl_FrontFacing == false) normal = -normal;
    vec3 lightDir = normalize(uLightPos - v_pos);
    float diffuseTerm = max(0.f, dot(normal, lightDir)); 
    vec3 Id = uLightIntensity * Kd * vec3(diffuseTerm);
    Id = Id / M_PI;

    oFragmentColor = vec4(Id, 1.f );
}