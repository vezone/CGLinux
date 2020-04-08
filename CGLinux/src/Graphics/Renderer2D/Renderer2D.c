#include "Renderer2D.h"

#include <glad/glad.h>
#include <Graphics/Shader.h>
#include <Utils/Logger.h>
#include "Utils/Array.h"
#include "Graphics/Constants.h"

BaseObject
renderer_create_colored_triangle()
{
	f32 vertices[] =
	{
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f,
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

	BaseObject triangle = {};
	glm_mat4_identity(triangle.Geometry.Transform);
	glm_vec3_zero(triangle.Geometry.Position);
	triangle.VertexArray = vao;
		
	return triangle;
}

void 
renderer_draw_colored_triangle(BaseObject* objectToDraw, Shader* shader, vec4 color, OrthographicCamera* camera)
{
	graphics_shader_bind(shader);

	mat4 transform = GLM_MAT4_IDENTITY_INIT;
	glm_translate(transform, objectToDraw->Geometry.Position);
	glm_mat4_copy(transform, objectToDraw->Geometry.Transform);
	
	graphics_shader_set_mat4(shader, "u_ViewProjection", 1, 0, camera->ViewProjectionMatrix[0]); 
	graphics_shader_set_mat4(shader, "u_Transform", 1, 0, objectToDraw->Geometry.Transform[0]);
	graphics_shader_set_float4(shader, "u_Color", 1, color);
	
	graphics_vertex_array_bind(&(objectToDraw->VertexArray));
	
	glDrawElements(GL_TRIANGLES, objectToDraw->VertexArray.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}

BaseObject
renderer_create_colored_rectangle()
{
	f32 x1 = -0.5f;
	f32 x2 = 0.5f;
	f32 y1 = -0.5f;
	f32 y2 = 0.5f;

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

	BaseObject coloredRectangle = {};
	glm_mat4_identity(coloredRectangle.Geometry.Transform);
	glm_vec3_zero(coloredRectangle.Geometry.Position);
	coloredRectangle.VertexArray = vao;
	
	return coloredRectangle;
}

void 
renderer_draw_colored_rectangle(BaseObject* objectToDraw, Shader* shader, vec4 color, OrthographicCamera* camera)
{
	graphics_shader_bind(shader);

	mat4 transform = GLM_MAT4_IDENTITY_INIT;
	glm_translate(transform, objectToDraw->Geometry.Position);
	glm_mat4_copy(transform, objectToDraw->Geometry.Transform);
	
	graphics_shader_set_mat4(shader, "u_ViewProjection", 1, 0, camera->ViewProjectionMatrix[0]); 
	graphics_shader_set_mat4(shader, "u_Transform", 1, 0, objectToDraw->Geometry.Transform[0]); 
	graphics_shader_set_float4(shader, "u_Color", 1, color); 

	graphics_vertex_array_bind(&(objectToDraw->VertexArray));
	
	glDrawElements(GL_TRIANGLES, objectToDraw->VertexArray.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}

BaseObject
renderer_create_textured_rectangle()
{
	f32 x1 = -0.5f;
	f32 x2 = 0.5f;
	f32 y1 = -0.5f;
	f32 y2 = 0.5f;
	
	f32 tx1 = (x1 >= 0.0f) ? 1.0f : 0.0f;
	f32 tx2 = (x2 >= 0.0f) ? 1.0f : 0.0f;
	f32 ty1 = (y1 >= 0.0f) ? 1.0f : 0.0f;
	f32 ty2 = (y2 >= 0.0f) ? 1.0f : 0.0f;

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

	BaseObject texturedRectangle = {};
	glm_mat4_identity(texturedRectangle.Geometry.Transform);
	glm_vec3_zero(texturedRectangle.Geometry.Position);
	texturedRectangle.VertexArray = vao;
	
	return texturedRectangle;
}

void
renderer_draw_textured_rectangle(BaseObject* objectToDraw, Shader* shader, Texture2D* texture, OrthographicCamera* camera)
{
	graphics_shader_bind(shader);
	graphics_texture2d_bind(texture, 0);

	mat4 transform = GLM_MAT4_IDENTITY_INIT;
	glm_translate(transform, objectToDraw->Geometry.Position);
	glm_mat4_copy(transform, objectToDraw->Geometry.Transform);
	
	graphics_shader_set_1int(shader, "u_Texture", 0); 
	graphics_shader_set_mat4(shader, "u_ViewProjection", 1, 0, camera->ViewProjectionMatrix[0]); 
	graphics_shader_set_mat4(shader, "u_Transform", 1, 0, objectToDraw->Geometry.Transform[0]);
	
	graphics_vertex_array_bind(&(objectToDraw->VertexArray));
	
	glDrawElements(GL_TRIANGLES, objectToDraw->VertexArray.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}


RectangleArray 
renderer_rectangle_array_create(OrthographicCamera* camera)
{
	i32 x, y, qlen, temp_index;
	u32 *indices;
	f32 *vertices, topx, topy, multiplier, tempPositionX, tempPositionY, heightMultiplier, widthMultiplier;
	RectangleGeometry position;
	Shader shader;
	
	shader = graphics_shader_compile(graphics_shader_load(shader_ss));

	//2550 * 2550 = 6 502 500
	qlen = 200;
	indices = NULL;
	vertices = NULL;
	multiplier = 1.1f;
	position = (RectangleGeometry) { -2.5f, -2.5f, 0.1f, 0.1f };
	heightMultiplier = position.Height * multiplier;
	widthMultiplier = position.Width * multiplier;
	
	for (x = 0; x < qlen; x++)
	{
		topx = position.TopX + x * widthMultiplier;
		tempPositionX = topx - position.Width;
		for (y = 0; y < qlen; y++)
		{
			topy = position.TopY + y * heightMultiplier;
			tempPositionY = topy - position.Height;
			temp_index = (y * 4) + (x * 4 * qlen);
			
			array_push(vertices, topx);
			array_push(vertices, topy);

			array_push(vertices, tempPositionX);
			array_push(vertices, topy);
			
			array_push(vertices, tempPositionX);
			array_push(vertices, tempPositionY);
			
			array_push(vertices, topx);
			array_push(vertices, tempPositionY);

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
	glm_mat4_identity(rectangleArray.Transform);
	rectangleArray.Camera = camera;

	return rectangleArray;
}

void 
renderer_rectangle_array_draw(RectangleArray array)
{
	graphics_shader_bind(&array.Shader);

	graphics_shader_set_mat4(&array.Shader, "u_ViewProjection", 1, 0, array.Camera->ViewProjectionMatrix[0]); 
	graphics_shader_set_mat4(&array.Shader, "u_Transform", 1, 0, array.Transform[0]);
	
	graphics_vertex_array_bind(&array.VAO);

	glDrawElements(GL_TRIANGLES, array.VAO.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}
