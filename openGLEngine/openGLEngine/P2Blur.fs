#version 330 core
out vec4 finalColor;

in vec2 pass_tex;
uniform sampler2D sampler;
const int kernelSize=10;
vec3 calculateColor()
{
  vec3 currentColor=vec3(0,0,0);
	for(int x=-kernelSize;x<=kernelSize;x++)
	{
	 currentColor+=texture(sampler,pass_tex+vec2(x,pass_tex.y)).xyz;
	}
  return currentColor/(kernelSize*kernelSize);
}
void main()
{
 finalColor=vec4(vec3(calculateColor()),1);
}