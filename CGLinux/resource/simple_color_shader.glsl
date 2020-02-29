#vertex shader
#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * position;
}

#fragment shader
#version 330 core
layout(location = 0) out vec4 o_Color;

uniform vec4 u_Color;

void main()
{
    o_Color = u_Color;
}