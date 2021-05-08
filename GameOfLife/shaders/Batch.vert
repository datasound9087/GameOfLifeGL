#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec4 col;

uniform mat4 prMatrix = mat4(1.0);
uniform mat4 vwMatrix = mat4(1.0);
uniform mat4 mdlMatrix = mat4(1.0);

out DATA
{
	vec4 color;
} vsOut;

void main()
{
	vsOut.color = col;

	gl_Position = prMatrix * vwMatrix * mdlMatrix * vec4(pos, 0.0, 1.0);
}
