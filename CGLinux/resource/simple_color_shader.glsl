#vertex shader
#version 330 core
layout(location = 0) in vec2 position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0, 1.0);
}

#fragment shader
#version 330 core
layout(location = 0) out vec4 o_Color;

uniform vec4 u_Color;

void main()
{
    o_Color = u_Color;
}