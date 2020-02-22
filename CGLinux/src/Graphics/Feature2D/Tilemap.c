#include "Tilemap.h"

#include <glad/glad.h>
#include <Graphics/Shader.h>
#include <Utils/Logger.h>

Quad 
renderer_quad_create(GPosition position, GColor color, u32 shared_shader, OrthographicCamera* camera)
{
	f32 quadVertices[] =
	{
		position.TopX, position.TopY, 0.0f,
		position.TopX + position.Height, position.TopY, 0.0f,
		position.TopX + position.Height, position.TopY - position.Height, 0.0f,
		position.TopX, position.TopY - position.Height, 0.0f
	};

	u32 indices[] = {
		0, 1, 2, 2, 3, 0
	};

	VertexBuffer vbo = {};
	graphics_vertex_buffer_create(&vbo, quadVertices, sizeof(quadVertices), Float3);
	graphics_vertex_buffer_bind(&vbo);

	IndexBuffer ibo = {};
	graphics_index_buffer_create(&ibo, indices, ARRAY_LENGTH(indices));
	graphics_index_buffer_bind(&ibo);

	VertexArray vao = {};
	graphics_vertex_array_create(&vao);
	graphics_vertex_array_add_vbo(&vao, vbo);
	graphics_vertex_array_add_ibo(&vao, ibo);
	graphics_vertex_array_bind(&vao);

	Quad quad = (Quad){ shared_shader, vao, position, color, camera };
	return quad;
}
void
renderer_quad_set_shader_default(Quad quad)
{
	graphics_shader_bind(quad.Shader);
	i32 location = glGetUniformLocation(quad.Shader, "u_Color");
	if (location >= 0)
	{
		static f32 inc = 0.1f;
		if (quad.Color.R > 1.0f)
		{
			inc = -0.1f;
		}
		else if (quad.Color.R < 0.0f) 
		{
			inc = 0.1f;
		}
		GLOG("inc: %f, R: %f\n", inc, quad.Color.R);
		quad.Color.R += inc;
		glUniform4f(location, 
			quad.Color.R, quad.Color.G, quad.Color.B, quad.Color.A);
	}
	else
	{
		GLOG(RED("location: %d\n"), location);
	}	
}

void
renderer_quad_draw(Quad quad)
{
	graphics_shader_bind(quad.Shader);

	orthographic_camera_recalculate_view_matrix(quad.camera);
	
	i32 location = glGetUniformLocation(quad.Shader, "u_ViewProjection");
	if (location >= 0)
	{
		glUniformMatrix4fv(location, 1, 0, quad.camera->ViewProjectionMatrix[0]);
	}
	graphics_vertex_array_bind(&(quad.VAO));
	
	glDrawElements(GL_TRIANGLES, quad.VAO.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}