#include "Renderer2D.h"

#include <glad/glad.h>
#include <Graphics/Shader.h>
#include <Graphics/Constants.h>
#include <Utils/Logger.h>
#include <Utils/Array.h>

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

/*
  Batch renderer
*/

static Shader* g_Shader;
static OrthographicCamera* g_Camera;
static BatchRenderer2DData g_RendererData =
{
	.DataCount = 0,
	.IndexCount = 0,
	.NextTextureIndex = 1
};

void
renderer_batch_init(Shader* shader, OrthographicCamera* camera)
{
    g_Shader = shader;
    g_Camera = camera;
  
	VertexBuffer vbo = {};
	graphics_vertex_buffer_allocate(
	    &vbo, VertexBufferSize);
	graphics_vertex_buffer_bind(&vbo);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float3);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float4);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float2);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float1);
	
	IndexBuffer ibo = {};
	fill_indices_array(g_RendererData.Indices, IndicesCount);
	graphics_index_buffer_create(&ibo, g_RendererData.Indices, IndicesCount);
	graphics_index_buffer_bind(&ibo);

	graphics_vertex_array_create(&g_RendererData.Vao);
	graphics_vertex_array_add_vbo(&g_RendererData.Vao, vbo);
	graphics_vertex_array_add_ibo(&g_RendererData.Vao, ibo);
	graphics_vertex_array_bind(&g_RendererData.Vao);
	
	Texture2D whiteTexture =  graphics_texture2d_create("CGLinux/resource/assets/textures/default/white_texture.png");
	g_RendererData.Textures[0] = whiteTexture; 
}

void
renderer_submit_rectangle(vec3 position, vec2 size, Texture2D* texture)
{
    i32 textureId;
    Quad quad = {};
	vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	if (g_RendererData.NextTextureIndex < 31)
	{
	  i8 isAlreadyInArray = -1;
	  for (i32 i = 1;
		   i < g_RendererData.NextTextureIndex;
		   i++)
	  {
		u32 id = g_RendererData.Textures[i].RendererID;
		if (id == texture->RendererID)
		{
		  isAlreadyInArray = i;
		  break;
		}
	  }

	  if (isAlreadyInArray != -1)
	  {
		textureId = isAlreadyInArray;
	  }
	  else
	  {
		textureId = g_RendererData.NextTextureIndex;
		g_RendererData.Textures[textureId] = *texture;
		++g_RendererData.NextTextureIndex;	  
	  }
	}
	else
	{
	  GLOG(RED("FLUSH!\n"));
	  renderer_flush();
	  textureId = 1;
	  g_RendererData.Textures[textureId] = *texture;
	  ++g_RendererData.NextTextureIndex;
	}
	
	fill_data_array(g_RendererData.Data, position, size, color, textureId, g_RendererData.DataCount);
	g_RendererData.DataCount  += QuadVerticesCount;
	g_RendererData.IndexCount += 6;
}

void
renderer_submit_colored_rectangle(vec3 position, vec2 size, vec4 color)
{
    i32 textureId;
    Quad quad = {};
	fill_data_array(g_RendererData.Data, position, size, color, 0, g_RendererData.DataCount);
	
	g_RendererData.DataCount  += QuadVerticesCount;
	g_RendererData.IndexCount += 6;
}

void
renderer_flush()
{
    graphics_shader_bind(g_Shader);	
	graphics_vertex_array_bind(&g_RendererData.Vao);
 
	i32 textureIndices[32];
	for (i32 i = 0; i < 32; i++)
	{
	  textureIndices[i] = i;
	}

	for (i32 i = 0; i < g_RendererData.NextTextureIndex; i++)
	{
	  graphics_texture2d_bind(&(g_RendererData.Textures[i]), i);
	}

	static i8 show = 1;
	if (show == 1)
	{
	  GDEBUG("DataCount: %d\n", g_RendererData.DataCount);
	  show = 0;
	}

	u32 size = g_RendererData.DataCount * sizeof(f32); 
	graphics_vertex_buffer_set_data(
   		g_RendererData.Vao.VertexBuffer,
		g_RendererData.Data, size);

	graphics_shader_set_mat4(g_Shader,
		"u_ViewProjection", 1, 0,
		g_Camera->ViewProjectionMatrix[0]); 
	graphics_shader_set_int1(g_Shader, "u_Textures", g_RendererData.NextTextureIndex, textureIndices);

	glDrawElements(GL_TRIANGLES,
				   g_RendererData.IndexCount,
				   GL_UNSIGNED_INT,
				   NULL);

	g_RendererData.DataCount  = 0;
	g_RendererData.IndexCount = 0;
	g_RendererData.NextTextureIndex = 1;
}
