#version 430

in float f_time;
in vec2 f_uvs;
in vec4 f_rgba;

out vec4 outColor; 

uniform sampler2D myTextureSampler;

void main() { 
    
    float j = f_time;
    if(mod(j,2) > 1) j = 1.0 - mod(j,1);
    else j = mod(j,1);

    // outColor = f_rgba * 0.8 + 0.2 * vec4(f_uvs, j, 1.0);
    outColor = texture(myTextureSampler, f_uvs) * 0.4 + f_rgba * 0.5 + 0.1 * vec4(f_uvs, j, 1.0);
    // outColor = texture(myTextureSampler, f_uvs);
}