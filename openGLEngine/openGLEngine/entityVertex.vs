#version 330 core
layout(location = 0) in vec3 attrib_pos;
layout(location = 1) in vec3 attrib_norm;
layout(location = 2) in vec2 attrib_tex;


uniform mat4 mat4_perspectiveMatrix;
uniform mat4 mat4_viewMatrix;
uniform mat4 mat4_modelMatrix;

out vec2 pass_tex;
out vec3 pass_norm;
out vec4 pass_pos;
void main()
{
	pass_tex=attrib_tex;
	pass_norm=mat3(mat4_modelMatrix)*attrib_norm;
	gl_Position=mat4_perspectiveMatrix*mat4_viewMatrix*mat4_modelMatrix*vec4(attrib_pos,1);
	pass_pos=mat4_modelMatrix*vec4(attrib_pos,1);
}