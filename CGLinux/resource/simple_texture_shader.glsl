#vertex shader
#version 330 core
layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec2 i_TextureCoordinates;

uniform mat4 u_ViewProjection;

out vec2 o_TextureCoordinates;

void main()
{
	o_TextureCoordinates = i_TextureCoordinates;
	gl_Position = u_ViewProjection * vec4(i_Position, 1.0);
}

#fragment shader
#version 330 core
layout(location = 0) out vec4 o_Color;

in vec2 o_TextureCoordinates;
uniform sampler2D u_Texture;

void main()
{
	o_Color = texture(u_Texture, o_TextureCoordinates);
	o_Color = vec4(o_TextureCoordinates, 0.0, 1.0);
}