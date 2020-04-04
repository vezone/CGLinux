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
		geometry.A[0], geometry.A[1],
		geometry.B[0], geometry.B[1],
		geometry.C[0], geometry.C[1],
	};

	u32 indices[] = {
		0, 1, 2
	};

	VertexBuffer vbo = {};
	graphics_vertex_buffer_create(&vbo, vertices, sizeof(vertices));
	graphics_vertex_buffer_bind(&vbo);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float2);

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
renderer_rectangle_create(RectangleGeometry geometry, GColor color, mat4 transform, OrthographicCamera* camera)
{
	graphics_shader_source source = graphics_shader_load(shader_ss);
	u32 shader = graphics_shader_compile(source);
	
	f32 x1 = geometry.TopX;
	f32 x2 = geometry.TopX + geometry.Width;
	f32 y1 = geometry.TopY;
	f32 y2 = geometry.TopY + geometry.Height;

	f32 vertices[] =
	{
		x1, y1, 	
		x2, y1, 	
		x2, y2, 	
		x1, y2	
	};

	u32 indices[] = {
		0, 1, 2, 2, 3, 0
	};

	VertexBuffer vbo = {};
	graphics_vertex_buffer_create(&vbo, vertices, sizeof(vertices));
	graphics_vertex_buffer_bind(&vbo);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float2);

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
	glm_mat4_copy(transform, rectangle.Transform);
	rectangle.Camera = camera;

	return rectangle;
}

void
renderer_rectangle_draw(Rectangle rectangle)
{
	graphics_shader_bind(rectangle.Shader);

	orthographic_camera_recalculate_view_matrix(rectangle.Camera);

	graphics_shader_uniform_mat4(rectangle.Shader, "u_ViewProjection", 1, 0, rectangle.Camera->ViewProjectionMatrix[0]); 
	graphics_shader_uniform_mat4(rectangle.Shader, "u_Transform", 1, 0, rectangle.Transform[0]); 

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
		x1, y1, tx1, ty1,
		x2, y1, tx2, ty1,
		x2, y2, tx2, ty2,
		x1, y2, tx1, ty2
	};

	u32 indices[] = {
		0, 1, 2, 2, 3, 0
	};

	VertexBuffer vbo = {};
	graphics_vertex_buffer_create(&vbo, vertices, sizeof(vertices));
	graphics_vertex_buffer_bind(&vbo);

	graphics_vertex_buffer_add_layout(&vbo, 0, Float2);
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
renderer_rectangle_array_create(mat4 transform, OrthographicCamera* camera)
{
	i32 x, y, qlen, temp_index;
	u32 *indices, shader;
	f32 *vertices, topx, topy, multiplier, temp_position_x, temp_position_y;
	RectangleGeometry position;
	
	shader = graphics_shader_compile(graphics_shader_load(shader_ss));

	//2550 * 2550 = 6 502 500
	qlen = 2000;
	indices = NULL;
	vertices = NULL;
	multiplier = 1.5f;
	position = (RectangleGeometry) { -2.5f, -2.5f, 0.01f, 0.01f };
	f32 heightMultiplier = position.Height * multiplier;
	f32 widthMultiplier = position.Width * multiplier;
	
	for (x = 0; x < qlen; x++)
	{
		topx = position.TopX + x * widthMultiplier;
		temp_position_x = topx - position.Width;
		for (y = 0; y < qlen; y++)
		{
			topy = position.TopY + y * heightMultiplier;
			temp_position_y = topy - position.Height;
			temp_index = (y * 4) + (x * 4 * qlen);
			
			array_push(vertices, topx);
			array_push(vertices, topy);

			array_push(vertices, temp_position_x);
			array_push(vertices, topy);
			
			array_push(vertices, temp_position_x);
			array_push(vertices, temp_position_y);
			
			array_push(vertices, topx);
			array_push(vertices, temp_position_y);

			array_push(indices, 0 + temp_index);
			array_push(indices, 1 + temp_index);
			array_push(indices, 2 + temp_index);
			array_push(indices, 2 + temp_index);
			array_push(indices, 3 + temp_index);
			array_push(indices, 0 + temp_index);
		}
	}
	
	VertexBuffer vbo = {};
	graphics_vertex_buffer_create(&vbo, vertices, array_len(vertices) * sizeof(f64));
	graphics_vertex_buffer_bind(&vbo);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float2);

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
	rectangleArray.VAO = vao;
	glm_mat4_copy(transform, rectangleArray.Transform);
	rectangleArray.Camera = camera;

	return rectangleArray;
}

void 
renderer_rectangle_array_draw(RectangleArray array)
{
	orthographic_camera_recalculate_view_matrix(array.Camera);
	
	graphics_shader_bind(array.Shader);

	graphics_shader_uniform_mat4(array.Shader, "u_ViewProjection", 1, 0, array.Camera->ViewProjectionMatrix[0]); 
	graphics_shader_uniform_mat4(array.Shader, "u_Transform", 1, 0, array.Transform[0]);
	
	graphics_vertex_array_bind(&array.VAO);

	glDrawElements(GL_TRIANGLES, array.VAO.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}
