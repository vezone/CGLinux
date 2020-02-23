#include "Tilemap.h"

#include <glad/glad.h>
#include <Graphics/Shader.h>
#include <Utils/Logger.h>
#include "Utils/Array.h"

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

QuadArray 
renderer_quad_array(u32 shader, OrthographicCamera* camera)
{
	float* vertices = NULL;
	//2550 * 2550 = 6 502 500
	i32 x, y, qlen = 2550;
	GPosition position = (GPosition) { -0.5f, -0.5f, 0.01f, 0.01f };
	u32* indices = NULL;
	f32 topx = position.TopX, topy = position.TopY;

	for (x = 0; x < qlen; x++)
	{
		position.TopX = topx + x * position.Width * 1.1f;
		for (y = 0; y < qlen; y++)
		{
			position.TopY = topy + y * position.Height * 1.1f;
			
			array_push(vertices, position.TopX);
			array_push(vertices, position.TopY);
			array_push(vertices, 0.0f);

			array_push(vertices, position.TopX + position.Width);
			array_push(vertices, position.TopY);
			array_push(vertices, 0.0f);
			
			array_push(vertices, position.TopX + position.Width);
			array_push(vertices, position.TopY - position.Height);
			array_push(vertices, 0.0f);
			
			array_push(vertices, position.TopX);
			array_push(vertices, position.TopY - position.Height);
			array_push(vertices, 0.0f);

			array_push(indices, 0 + (y * 4) + (x * 4 * qlen));
			array_push(indices, 1 + (y * 4) + (x * 4 * qlen));
			array_push(indices, 2 + (y * 4) + (x * 4 * qlen));
			array_push(indices, 2 + (y * 4) + (x * 4 * qlen));
			array_push(indices, 3 + (y * 4) + (x * 4 * qlen));
			array_push(indices, 0 + (y * 4) + (x * 4 * qlen));
		}
		position.TopY = topy;
	}

	VertexBuffer vbo = {};
	graphics_vertex_buffer_create(&vbo, vertices, array_len(vertices)*sizeof(f32), Float3);
	graphics_vertex_buffer_bind(&vbo);

	IndexBuffer ibo = {};
	graphics_index_buffer_create(&ibo, indices, array_len(indices));
	graphics_index_buffer_bind(&ibo);

	VertexArray vao = {};
	graphics_vertex_array_create(&vao);
	graphics_vertex_array_add_vbo(&vao, vbo);
	graphics_vertex_array_add_ibo(&vao, ibo);
	graphics_vertex_array_bind(&vao);

	QuadArray quadArray = {};
	quadArray.Shader = shader;
	quadArray.VertexArray = vao;
	quadArray.Camera = camera;

	return quadArray;
}


void 
renderer_quad_array_draw(QuadArray array)
{
	orthographic_camera_recalculate_view_matrix(array.Camera);
	
	graphics_shader_bind(array.Shader);
	i32 location = glGetUniformLocation(array.Shader, "u_ViewProjection");
	if (location >= 0)
	{
		glUniformMatrix4fv(location, 1, 0, array.Camera->ViewProjectionMatrix[0]);
	}
	
	graphics_vertex_array_bind(&array.VertexArray);

	glDrawElements(GL_TRIANGLES, array.VertexArray.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}