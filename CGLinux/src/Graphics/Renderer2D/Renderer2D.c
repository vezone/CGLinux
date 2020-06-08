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
renderer_create_colored_rectangle(f32 x1, f32 x2, f32 y1, f32 y2)
{
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
renderer_create_textured_rectangle(f32 x, f32 y)
{
    f32 size = 1.0f;
	f32 tx1 = (x >= 0.0f) ? 1.0f : 0.0f;
	f32 tx2 = ((x + size) >= 0.0f) ? 1.0f : 0.0f;
	f32 ty1 = (y >= 0.0f) ? 1.0f : 0.0f;
	f32 ty2 = ((y + size) >= 0.0f) ? 1.0f : 0.0f;

	f32 vertices[] =
	{
		x, y, tx1, ty1,
		x, (y + size), tx1, ty2,
		(x + size), (y + size), tx2, ty2,
		(x + size), y, tx2, ty1
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
#if 0
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
	graphics_vertex_buffer_create(&vbo, vertices, array_len(vertices) * sizeof(f32));
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
#endif
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


/*
  Batch renderer
*/

ColoredBatchRenderer2DData Renderer2DData =
{
	.DataCount = 0,
	.IndexCount = 0
};

void
fill_indices_array(u32* indices, u32 length)
{
    i32 i;
    u32 temp = 0;
    for (i = 0; i < length; i += 6)
	{
	    indices[i]     = 0 + temp;
	    indices[i + 1] = 1 + temp;
	    indices[i + 2] = 2 + temp;
	    indices[i + 3] = 2 + temp;
	    indices[i + 4] = 3 + temp;
	    indices[i + 5] = 0 + temp;
	    temp += 4;
	}
}

void
quad_fill_data_to_array(f32* destination, Quad* source, u32 start_index)
{
    i32 i = start_index;
	i32 s = 0;
	i32 number_of_vertices = start_index + (6 * 4);
	for ( ;i < number_of_vertices; )
	{
	   QuadVertex vertex = source->vertex[s];
	   s++;
	   
	   destination[i++] = vertex.Position[0];
	   destination[i++] = vertex.Position[1];
	   
	   destination[i++] = vertex.Color[0];
	   destination[i++] = vertex.Color[1];
	   destination[i++] = vertex.Color[2];
	   destination[i++] = vertex.Color[3];
	}
}

void
quad_vertex_create_color(Quad* quad, vec3 position, vec2 size, vec4 c11)
{
	quad->vertex[0].Position[0] = position[0];
	quad->vertex[0].Position[1] = position[1];
	quad->vertex[1].Position[0] = position[0];
	quad->vertex[1].Position[1] = position[1] + size[1];
	quad->vertex[2].Position[0] = position[0] + size[0];
	quad->vertex[2].Position[1] = position[1] + size[1];
	quad->vertex[3].Position[0] = position[0] + size[0];
	quad->vertex[3].Position[1] = position[1];
       
	glm_vec4_copy(c11, quad->vertex[0].Color);
	glm_vec4_copy(c11, quad->vertex[1].Color);
	glm_vec4_copy(c11, quad->vertex[2].Color);
	glm_vec4_copy(c11, quad->vertex[3].Color);
	
	quad->IsSolidColor = 1;
}

//NOTE(vez): we are not handle z axis for now
//size[0] - width
//size[1] - height
void
quad_vertex_create_gradient(Quad* quad, vec3 position, vec2 size, vec4 c11, vec4 c12, vec4 c22, vec4 c21)
{
	quad->vertex[0].Position[0] = position[0];
	quad->vertex[0].Position[1] = position[1];
	quad->vertex[1].Position[0] = position[0];
	quad->vertex[1].Position[1] = position[1] + size[1];
	quad->vertex[2].Position[0] = position[0] + size[0];
	quad->vertex[2].Position[1] = position[1] + size[1];
	quad->vertex[3].Position[0] = position[0] + size[0];
	quad->vertex[3].Position[1] = position[1];
    
	glm_vec4_copy(c11, quad->vertex[0].Color);
	glm_vec4_copy(c12, quad->vertex[1].Color);
	glm_vec4_copy(c22, quad->vertex[2].Color);
	glm_vec4_copy(c21, quad->vertex[3].Color);
}

void
color_renderer_batch_init()
{
	VertexBuffer vbo = {};
	graphics_vertex_buffer_allocate(
	    &vbo,
		SizeofVertices);
	graphics_vertex_buffer_bind(&vbo);

	graphics_vertex_buffer_add_layout(&vbo, 0, Float2);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float4);
	
	IndexBuffer ibo = {};
	fill_indices_array(Renderer2DData.Indices, MaxIndices);
	graphics_index_buffer_create(&ibo, Renderer2DData.Indices, MaxIndices);
	graphics_index_buffer_bind(&ibo);

	graphics_vertex_array_create(&Renderer2DData.Vao);
	graphics_vertex_array_add_vbo(&Renderer2DData.Vao, vbo);
	graphics_vertex_array_add_ibo(&Renderer2DData.Vao, ibo);
	graphics_vertex_array_bind(&Renderer2DData.Vao);
	
	glm_mat4_identity(Renderer2DData.Transform);
}

void
color_renderer_submit_rectangle(vec3 position, vec2 size, i8 isSolid, vec4 c11, vec4 c12, vec4 c22, vec4 c21)
{
	Quad quad = {};
	if (isSolid)
	{
	  quad_vertex_create_color(&quad, position, size, c11);  
	}
	else
	{
	  quad_vertex_create_gradient(&quad, position, size, c11, c12, c21, c22);	
	}

	quad_fill_data_to_array(Renderer2DData.Data, &quad, Renderer2DData.DataCount);
	
	Renderer2DData.DataCount  += (4 * 6);
	Renderer2DData.IndexCount += 6;
}

void
color_renderer_flush(Shader* shader, OrthographicCamera* camera)
{
	graphics_shader_bind(shader);	

	graphics_vertex_array_bind(&(Renderer2DData.Vao));

	u32 size = Renderer2DData.DataCount * sizeof(f32); 
	graphics_vertex_buffer_set_data(
   		Renderer2DData.Vao.VertexBuffer,
		Renderer2DData.Data, size);
	
	mat4 transform = GLM_MAT4_IDENTITY_INIT;
	glm_mat4_copy(transform, Renderer2DData.Transform);

	graphics_shader_set_mat4(shader,
							"u_ViewProjection", 1, 0,
							camera->ViewProjectionMatrix[0]); 
	graphics_shader_set_mat4(shader,
							 "u_Transform",
							 1, 0,
							 Renderer2DData.Transform[0]);
	
	glDrawElements(GL_TRIANGLES,
				   Renderer2DData.IndexCount,
				   GL_UNSIGNED_INT,
				   NULL);

	Renderer2DData.DataCount  = 0;
	Renderer2DData.IndexCount = 0;
}

