#version 330 core
layout(location = 0) in vec3 attrib_pos;
layout(location = 1) in vec3 attrib_norm;
layout(location = 2) in vec2 attrib_tex;

uniform vec2 textBottomLeftLocation;
uniform vec2 glyphSize;
uniform vec2 screenSize;

out vec2 pass_tex;
void main()
{
 pass_tex=vec2(attrib_pos.xz);


 vec2 pos=attrib_pos.xz;
 pos=pos*glyphSize;
 pos=pos+textBottomLeftLocation;
 pos=pos/screenSize;
 pos=vec2(2*pos.x-1,2*pos.y-1);
 gl_Position=vec4(pos.x,pos.y,0,1);
}