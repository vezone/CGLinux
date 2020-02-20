#vertex shader
#version 330 core
layout(location = 0) in vec4 position;

out vec4 o_Position;
uniform mat4 u_srcs_RotationMatrix;
uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection*u_srcs_RotationMatrix*position;
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