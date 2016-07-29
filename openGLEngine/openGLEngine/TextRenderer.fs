#version 330 core
out vec4 finalColor;

in vec2 pass_tex;
uniform sampler2D sampler;

uniform vec2 glyphSize;
uniform float atlasTextureSize;
uniform float glyphsPerRow;
uniform float glyphCode;
uniform vec3 textColor;

void main()
{
  float currentRow=float(int(glyphCode)/int(glyphsPerRow));
  if(mod(glyphCode,glyphsPerRow)==0)
  {
  currentRow=currentRow-1;
  }
  float currentColumn=mod(glyphCode-1,glyphsPerRow)+1;
  vec2 uv=vec2(0,0);
  uv.x=((currentColumn+pass_tex.x-1)*glyphSize.x)/atlasTextureSize;
  uv.y=1-(glyphSize.y*(currentRow+1-pass_tex.y)/atlasTextureSize);


 if(texture(sampler,uv).xyz==vec3(1,0,1)||glyphCode==0)
 {
	discard;
 }
 finalColor=vec4(textColor,1);
}