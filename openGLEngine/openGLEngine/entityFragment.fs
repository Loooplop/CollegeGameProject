#version 330 core
out vec4 finalColor;

uniform sampler2D sampler;

uniform vec3 light_position;
uniform vec3 light_color;
uniform vec3 light_attenuation;
uniform vec3 vec3_cameraOrigin;

in vec2 pass_tex;
in vec3 pass_norm;
in vec4 pass_pos;
void main()
{
	
	vec3 toLightVector=normalize(light_position-pass_pos.xyz);
	float angle=clamp(dot(pass_norm,toLightVector),0.1,1.0);
	vec3 diffuseLight=angle*light_color;

	vec3 toCameraVector=normalize(vec3_cameraOrigin-pass_pos.xyz);
	vec3 reflectedVector=reflect(-toLightVector,pass_norm);

	float specularAngle=dot(reflectedVector,toCameraVector);
	float distance=length(light_position-pass_pos.xyz);
	float att=(light_attenuation.x+distance*light_attenuation.y+distance*distance*light_attenuation.z);

    finalColor=texture(sampler,pass_tex)*vec4((diffuseLight+vec3(1,1,1)*pow(max(0.0,specularAngle),64))/att,1);
	//float amount=(finalColor.x+finalColor.y+finalColor.z)/3;
	//finalColor=vec4(amount,amount,amount,1.0);
	finalColor=vec4(1,0,0,1);
}