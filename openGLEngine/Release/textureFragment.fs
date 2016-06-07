#version 330 core
out vec4 finalColor;

in vec2 pass_tex;

uniform sampler2D sampler;
void main()
{

 finalColor=texture(sampler,pass_tex);

}