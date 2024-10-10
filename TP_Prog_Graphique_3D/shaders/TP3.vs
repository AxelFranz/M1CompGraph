#version 430

// INPUT
layout(location = 1) in vec2 position_in;
layout(location = 2) in vec2 coord2d;

// OUTPUT
// UNIFORM
layout(location = 0) uniform mat4 uModelMatrix;
layout(location = 1) uniform mat4 uViewMatrix;
layout(location = 2) uniform mat4 uProjectionMatrix;
layout(location = 3) uniform float uHeightScale;



layout(binding = 0) uniform sampler2D uSampler;

out vec2 uv;
out float height;


// MAIN PROGRAM
void main()
{
	// - write position with matrix transformations into screen space
	vec3 position = vec3(position_in.xy,uHeightScale*texture(uSampler,coord2d));
	height = position.z;
	vec4 posXYZ = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(position,1.0);
	gl_Position = posXYZ;
	uv = coord2d;
}