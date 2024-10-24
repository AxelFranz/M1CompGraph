#version 430
precision highp float;

#define M_PI 3.14159265358979

// INPUT

// UNIFORM
// Material (BRDF: bidirectional reflectance distribution function)
layout(binding = 0) uniform sampler2D uPosition; // diffuse
layout(binding = 1) uniform sampler2D uNormals; // diffuse
layout(binding = 2) uniform sampler2D uAlbedo; // diffuse
layout(binding = 3) uniform sampler2D uKs; // diffuse
// Light (Point light)
layout(location = 5) uniform float lightIntensity;
layout(location = 6) uniform int nb_lum;
uniform vec3 pos_lum[100];
uniform vec3 col_lum[100];

in vec2 texCoord;
// OUTPUT
out vec4 oFragmentColor;

// MAIN PROGRAM
void main()
{
	float uNs = 256;
	// --------------------------------------
	// Lighting and shading: PER-FRAGMENT
	// - here, we "retrieve" mandatory information from the vertex shader (i.e. "position" and "normal")
	// --------------------------------------

 	ivec2 icoord = ivec2(gl_FragCoord.xy);
	vec3 v_position = vec3(texelFetch(uPosition,icoord,0));
	vec3 v_normal = vec3(texelFetch(uNormals,icoord,0));
	vec3 albedo = vec3(texelFetch(uAlbedo,icoord,0));
	vec3 Ks = vec3(texelFetch(uKs, icoord, 0));

	vec3 p = v_position;
	vec3 n = normalize(v_normal); // interpolated normal direction from current interpolated position in View space
	
	vec3 color = vec3(0);

	for (int i = 0; i < nb_lum; ++i)
	{
		// Reflected diffuse intensity
		vec3 lightDir = normalize(pos_lum[i] - p); // "light direction" from current interpolated position in View space
		float diffuseTerm = max(0.f, dot(n, lightDir)); // "max" is used to avoir "back" lighting (when light is behind the object)
		vec3 Id = (col_lum[i] * lightIntensity) * albedo * vec3(diffuseTerm);
		Id = Id / M_PI; // normalization of the diffuse BRDF (for energy conservation)
		vec3 Is = vec3(0.0);
  	    if(diffuseTerm > 0.0) {
     	   vec3 viewDir = normalize(-v_position); // "view direction" from current vertex position => because, in View space, "dir = vec3(0.0, 0.0, 0.0) - p"
     	   vec3 halfDir = normalize(viewDir + lightDir); // half-vector between view and light vectors
     	   float specularTerm = max(0.0, pow(dot(n, halfDir), uNs)); // "Ns" control the size of the specular highlight
     	   Is = lightIntensity * Ks * vec3(specularTerm);
     	   Is /= (uNs + 2.) / (2. * M_PI); // normalization of the specular BRDF (for energy conservation)
    	}

		// Reflected intensity accumulation (i.e final color)
		color += (0.6 * Id + 0.3 * Is);
	}
	// --------------------------------------
	
	oFragmentColor = vec4(color, 1.f);
}