#version 430
precision highp float;

// OUTPUT
out vec4 oFragmentColor;
in vec2 texCoord;

float noise(vec2 st)
{
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

float dot2( in vec2 v ) { return dot(v,v); }



float sdCircle( vec2 p, float r )
{
    return length(p) - r;
} 

float sdHeart( in vec2 p )
{
    p.x = abs(p.x);

    if( p.y+p.x>1.0 )
        return sqrt(dot2(p-vec2(0.25,0.75))) - sqrt(2.0)/4.0;
    return sqrt(min(dot2(p-vec2(0.00,1.00)),
                    dot2(p-0.5*max(p.x+p.y,0.0)))) * sign(p.x-p.y);
}

// MAIN PROGRAM
void main()
{
    float heart = sdHeart(2*(texCoord-vec2(0.5f,0.25f)));
    //vec3 color  = vec3(heart);
    float isin = step(0,heart);
    vec3 color;
    if( isin == 0) {
        color = vec3(1.f,0.f,0.f);
    } else {
        color = vec3(1.f);
    }
    //oFragmentColor = vec4(color,1.f);
    oFragmentColor = vec4(mod(5.0 * texCoord, 0.2)+vec2(0.2f),0.f,1.f);
}