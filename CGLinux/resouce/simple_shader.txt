#vertex shader
#version 330 core
layout(location = 0) in vec3 a_Position;
out vec4 o_Position;
void main()
{
	gl_Position = vec4(a_Position, 1.0);
	o_Position = gl_Position;
}

#fragment shader
#version 330 core
layout(location = 0) out vec4 o_Color;
in vec4 o_Position;
void main()
{
	o_Color = o_Position * 0.5 + 0.5;
}