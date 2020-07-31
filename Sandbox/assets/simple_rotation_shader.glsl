#vertex shader
#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 u_RotationMatrix;

void main()
{
    gl_Position = u_RotationMatrix * position;
}

#fragment shader
#version 330 core
layout(location = 0) out vec4 o_Color;

void main()
{
    o_Color = vec4(0.2f, 0.7f, 1.0f, 1.0f);
}