#version 330 core
layout(location = 0) in vec3 attrib_pos;
layout(location = 1) in vec3 attrib_norm;
layout(location = 2) in vec2 attrib_tex;


out vec2 pass_tex;
void main()
{
 pass_tex=vec2(0.5f+attrib_pos.x/2,0.5f+attrib_pos.z/2);
 gl_Position=vec4(attrib_pos.xzy,1);
}