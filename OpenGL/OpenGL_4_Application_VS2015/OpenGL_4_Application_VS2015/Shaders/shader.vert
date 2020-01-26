#version 400
layout(location = 0) in vec3 positions;
uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;
uniform float time;
const float amplitude=0.200;
const float frequency=4;
const float PHI=3.14159;

void main()
{
	float y=amplitude*sin(-PHI*length(positions)*frequency+time);
	gl_Position=perspective*view*model*vec4(positions.x,y,positions.z,1.0f);
	//gl_Position=model*vec4(positions,1.0f);
}