#version 430

layout(location = 1) in vec3 position_in;
layout(location = 2) in vec3 normal;

layout (location = 0) uniform mat4 modelMatrix;
layout (location = 1) uniform mat4 viewMatrix;
layout (location = 2) uniform mat4 projectionMatrix;
layout (location = 3) uniform mat3 invTrans;

out vec3 m_norm;
out vec4 m_pos; 

void main()
{
	m_pos = modelMatrix * vec4(position_in,1);
	m_norm = invTrans*normal;
	gl_Position = projectionMatrix * viewMatrix * m_pos;
}