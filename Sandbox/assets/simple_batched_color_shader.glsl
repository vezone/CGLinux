#vertex shader
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;

out vec4 o_color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0, 1.0);
	o_color = color;
}

#fragment shader
#version 330 core
layout(location = 0) out vec4 o_Color;

in vec4 o_color;

void main()
{
    o_Color = o_color;
}