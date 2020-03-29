#include "Renderer2D.h"

#include <glad/glad.h>
#include <Graphics/Shader.h>
#include <Utils/Logger.h>
#include "Utils/Array.h"
#include "Graphics/Constants.h"

Triangle
renderer_triangle_create(TriangleGeometry geometry, GColor color, mat4 transform, OrthographicCamera* camera)
{
	graphics_shader_source shader_source =  graphics_shader_load(shader_ss);
	u32 shader = 
		graphics_shader_compile(shader_source);
	
	f32 vertices[] =
	{
		geometry.A[0], geometry.A[1], 0.0f,
		geometry.B[0], geometry.B[1], 0.0f,
		geometry.C[0], geometry.C[1], 0.0f
	};

	u32 indices[] = {
		0, 1, 2
	};

	VertexBuffer vbo = {};
	graphics_vertex_buffer_create(&vbo, vertices, sizeof(vertices));
	graphics_vertex_buffer_bind(&vbo);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float3);

	IndexBuffer ibo = {};
	graphics_index_buffer_create(&ibo, indices, ARRAY_LENGTH(indices));
	graphics_index_buffer_bind(&ibo);

	VertexArray vao = {};
	graphics_vertex_array_create(&vao);
	graphics_vertex_array_add_vbo(&vao, vbo);
	graphics_vertex_array_add_ibo(&vao, ibo);
	graphics_vertex_array_bind(&vao);

	Triangle triangle = {};
	triangle.Shader = shader;
	triangle.VAO = vao;
	triangle.Geometry = geometry;
	triangle.Color = color;
	glm_mat4_copy(transform, triangle.Transform);
	triangle.Camera = camera;
	
	return triangle;
}

void 
renderer_triangle_draw(Triangle triangle)
{
	graphics_shader_bind(triangle.Shader);

	orthographic_camera_recalculate_view_matrix(triangle.Camera);

	graphics_shader_uniform_mat4(triangle.Shader, "u_ViewProjection", 1, 0, triangle.Camera->ViewProjectionMatrix[0]); 
	graphics_shader_uniform_mat4(triangle.Shader, "u_Transform", 1, 0, triangle.Transform[0]); 
	
	graphics_vertex_array_bind(&(triangle.VAO));
	
	glDrawElements(GL_TRIANGLES, triangle.VAO.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}

Rectangle 
renderer_rectangle_create(RectangleGeometry geometry, GColor color, OrthographicCamera* camera)
{
	u32 shader = 
		graphics_shader_compile(graphics_shader_load(shader_ss));

	f32 vertices[] =
	{
		geometry.TopX, geometry.TopY, 0.0f,
		geometry.TopX + geometry.Width, geometry.TopY, 0.0f,
		geometry.TopX + geometry.Width, geometry.TopY - geometry.Height, 0.0f,
		geometry.TopX, geometry.TopY - geometry.Height, 0.0f
	};

	u32 indices[] = {
		0, 1, 2, 2, 3, 0
	};

	VertexBuffer vbo = {};
	graphics_vertex_buffer_create(&vbo, vertices, sizeof(vertices));
	graphics_vertex_buffer_bind(&vbo);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float3);

	IndexBuffer ibo = {};
	graphics_index_buffer_create(&ibo, indices, ARRAY_LENGTH(indices));
	graphics_index_buffer_bind(&ibo);

	VertexArray vao = {};
	graphics_vertex_array_create(&vao);
	graphics_vertex_array_add_vbo(&vao, vbo);
	graphics_vertex_array_add_ibo(&vao, ibo);
	graphics_vertex_array_bind(&vao);

	Rectangle rectangle = {};
	rectangle.Shader = shader;
	rectangle.VAO = vao;
	rectangle.Geometry = geometry;
	rectangle.Color = color;
	rectangle.Camera = camera;

	return rectangle;
}

void
renderer_rectangle_draw(Rectangle rectangle)
{
	graphics_shader_bind(rectangle.Shader);

	orthographic_camera_recalculate_view_matrix(rectangle.Camera);
	graphics_shader_uniform_mat4(rectangle.Shader, "u_ViewProjection", 1, 0, rectangle.Camera->ViewProjectionMatrix[0]); 
	
	graphics_vertex_array_bind(&(rectangle.VAO));
	
	glDrawElements(GL_TRIANGLES, rectangle.VAO.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}

TexturedRectangle 
renderer_create_textured_rectangle(RectangleGeometry geometry, const char* texturePath, OrthographicCamera* camera)
{
	u32 shader = 
		graphics_shader_compile(graphics_shader_load(shader_sts));

	Texture2D texture = graphics_texture2d_create(texturePath);
	graphics_texture2d_bind(&texture, 0);

	f32 x1 = geometry.TopX;
	f32 x2 = geometry.TopX + geometry.Width;
	f32 y1 = geometry.TopY;
	f32 y2 = geometry.TopY + geometry.Height;

	f32 tx1 = (x1 >= 0.0f) ? 1.0f : 0.0f;
	f32 tx2 = (x2 >= 0.0f) ? 1.0f : 0.0f;
	f32 ty1 = (y1 >= 0.0f) ? 1.0f : 0.0f;
	f32 ty2 = (y2 >= 0.0f) ? 1.0f : 0.0f;

	GDEBUG("x1: %f, y1: %f, x2: %f, y2: %f\n", x1, y1, x2, y2);
	GDEBUG("tx1: %f, ty1: %f, tx2: %f, ty2: %f\n", tx1, ty1, tx2, ty2);

	f32 vertices[] =
	{
		x1, y1, 0.0f, tx1, ty1,
		x2, y1, 0.0f, tx2, ty1,
		x2, y2, 0.0f, tx2, ty2,
		x1, y2, 0.0f, tx1, ty2
	};

	u32 indices[] = {
		0, 1, 2, 2, 3, 0
	};

	VertexBuffer vbo = {};
	graphics_vertex_buffer_create(&vbo, vertices, sizeof(vertices));
	graphics_vertex_buffer_bind(&vbo);

	graphics_vertex_buffer_add_layout(&vbo, 0, Float3);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float2);

	IndexBuffer ibo = {};
	graphics_index_buffer_create(&ibo, indices, ARRAY_LENGTH(indices));
	graphics_index_buffer_bind(&ibo);

	VertexArray vao = {};
	graphics_vertex_array_create(&vao);
	graphics_vertex_array_add_vbo(&vao, vbo);
	graphics_vertex_array_add_ibo(&vao, ibo);
	graphics_vertex_array_bind(&vao);

	TexturedRectangle rectangle = {};
	rectangle.Shader = shader;
	rectangle.Texture = texture;
	rectangle.VAO = vao;
	rectangle.Geometry = geometry;
	rectangle.Camera = camera;

	return rectangle;
}

void 
renderer_textured_rectangle_draw(TexturedRectangle rectangle)
{
	graphics_shader_bind(rectangle.Shader);
	graphics_texture2d_bind(&rectangle.Texture, 0);

	orthographic_camera_recalculate_view_matrix(rectangle.Camera);

	graphics_shader_uniform1i(rectangle.Shader, "u_Texture", 0); 
	graphics_shader_uniform_mat4(rectangle.Shader, "u_ViewProjection", 1, 0, rectangle.Camera->ViewProjectionMatrix[0]); 
	
	graphics_vertex_array_bind(&(rectangle.VAO));
	
	glDrawElements(GL_TRIANGLES, rectangle.VAO.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}

RectangleArray 
renderer_rectangle_array_create(OrthographicCamera* camera)
{
	u32 shader = 
		graphics_shader_compile(graphics_shader_load(shader_ss));

	//2550 * 2550 = 6 502 500
	i32 x, y, qlen = 500;
	RectangleGeometry position = (RectangleGeometry) { 
		-3.5f, -3.5f, 0.05f, 0.05f 
	};
	f32* vertices = NULL;
	u32* indices = NULL;
	f32  topx = position.TopX, topy = position.TopY;
	f32  multiplier = 1.1f;
	for (x = 0; x < qlen; x++)
	{
		position.TopX = topx + x * position.Width * multiplier;
		for (y = 0; y < qlen; y++)
		{
			position.TopY = topy + y * position.Height * multiplier;
			
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
	graphics_vertex_buffer_create(&vbo, vertices, array_len(vertices)*sizeof(f32));
	graphics_vertex_buffer_bind(&vbo);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float3);

	IndexBuffer ibo = {};
	graphics_index_buffer_create(&ibo, indices, array_len(indices));
	graphics_index_buffer_bind(&ibo);

	VertexArray vao = {};
	graphics_vertex_array_create(&vao);
	graphics_vertex_array_add_vbo(&vao, vbo);
	graphics_vertex_array_add_ibo(&vao, ibo);
	graphics_vertex_array_bind(&vao);

	RectangleArray rectangleArray = {};
	rectangleArray.Shader = shader;
	rectangleArray.VertexArray = vao;
	rectangleArray.Camera = camera;

	return rectangleArray;
}

void 
renderer_rectangle_array_draw(RectangleArray array)
{
	orthographic_camera_recalculate_view_matrix(array.Camera);
	
	graphics_shader_bind(array.Shader);

	graphics_shader_uniform_mat4(array.Shader, "u_ViewProjection", 1, 0, array.Camera->ViewProjectionMatrix[0]); 
	
	graphics_vertex_array_bind(&array.VertexArray);

	glDrawElements(GL_TRIANGLES, array.VertexArray.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}
