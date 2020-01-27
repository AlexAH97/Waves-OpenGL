#version 400
layout(location = 0) in vec3 positions;
uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;
uniform float time;
const float amplitude=0.050;
const float frequency=4;
const float PI=3.14159;

void main()
{
	float y=amplitude*(cos(-PI*length(positions)*frequency+time)+sin(-PI*length(positions)*frequency+time));
	gl_Position=perspective*view*model*vec4(positions.x,y,positions.z,1.0f);
	
}