#version 330 core
out vec4 finalColor;

in vec2 pass_tex;
uniform sampler2D sampler;

void main()
{
 float n=0.1f;
 float f=100.0f;
 float z = (2 * n) / (f + n - texture2D( sampler, pass_tex ).x * (f - n));
 vec3 outColor=vec3(z,z,z);
 finalColor=vec4(outColor,1);

}