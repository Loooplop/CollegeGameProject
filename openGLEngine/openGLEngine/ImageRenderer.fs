#version 330 core
out vec4 finalColor;

in vec2 pass_tex;
uniform sampler2D sampler;

void main()
{
 vec3 outColor=vec3(texture(sampler,pass_tex).x,texture(sampler,pass_tex).y,texture(sampler,pass_tex).z);
 finalColor=vec4(outColor,1);

}