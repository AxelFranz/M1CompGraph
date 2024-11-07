#version 430
precision highp float;

#define M_PI 3.14159265358979

out vec3 frag_out;

in vec3 m_norm;
in vec4 m_pos;

layout(location = 4) uniform vec3 ualbedo;
layout(location = 5) uniform vec3 pos_lum[4];
layout(location = 9) uniform vec3 col_lum[4];
layout(location = 13) uniform bool atten;
layout(location = 14) uniform bool correc;
layout(location = 15) uniform bool tone;
layout(location = 16) uniform float exposure;

void main()
{
    vec3 n = normalize(m_norm);
    if(!gl_FrontFacing) {
        n = -n;
    }
    vec3 albedo = ualbedo;
    vec3 color = vec3(0.f);
    vec3 p = m_pos.xyz;

    for(int i = 0; i < 4; i++) {
        vec3 light_dir = normalize(pos_lum[i] - p);
        float diffus = max(0,dot(n,light_dir));
        vec3 Id = col_lum[i] * albedo * diffus;
        if(atten && correc) {
            Id = Id/(pow(length(pos_lum[i] - p), 2));
        }
        if(atten) {
            Id = Id/(length(pos_lum[i] - p));
        }
        color += Id;
    }

    float power = 1.0f/2.2f;
    if(correc) {
        color = vec3(pow(color,power));
    }

    if(tone) {
        color=vec3(1-exp(-color*exposure));
    }
        

    frag_out = color;


}
