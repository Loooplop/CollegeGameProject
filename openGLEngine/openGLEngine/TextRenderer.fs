#version 330 core
out vec4 finalColor;

in vec2 pass_tex;
uniform sampler2D sampler;

uniform vec2 fontUVSize;
uniform vec2 UVGlyphBottomLocation;
uniform vec3 textColor;

void main()
{
 if(texture(sampler,vec2(UVGlyphBottomLocation.x+(pass_tex.x*fontUVSize.x),UVGlyphBottomLocation.y+(pass_tex.y*fontUVSize.y))).xyz==vec3(1,0,1))
 {
	discard;
 }
 finalColor=vec4(textColor,1);
}