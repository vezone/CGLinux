#pragma once

#include "cglm/cglm.h"
#include "Graphics/Buffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Renderer2D/OrthographicCamera.h"
#include "Graphics/Texture2D.h"
#include "Utils/Types.h"
#include "Utils/Array.h"

typedef struct BaseGeometry
{
	/*
	  if we want to move object at x coord:
	      instance.Position[0] += 0.1;
	  in update function we should do smth like that:
	      glm_translate(rectangle.Transform, rectangle.Position);
	 */
	vec3 Position;
	mat4 Transform;
} BaseGeometry;

typedef struct BaseObject
{
	BaseGeometry Geometry;
	VertexArray VertexArray;
} BaseObject;

static void
base_geometry_update_position(BaseObject* object)
{
	glm_translate(object->Geometry.Transform, object->Geometry.Position);
}

typedef struct RectangleArray {
	Shader Shader;
	VertexArray VAO;
	mat4 Transform;
    OrthographicCamera* Camera;
} RectangleArray;

BaseObject
renderer_create_colored_triangle();
void
renderer_draw_colored_triangle(BaseObject* objectToDraw, Shader* shader, vec4 color, OrthographicCamera* camera);

BaseObject 
renderer_create_colored_rectangle(f32 x1, f32 x2, f32 y1, f32 y2);
void 
renderer_draw_colored_rectangle(BaseObject* objectToDraw, Shader* shader, vec4 color, OrthographicCamera* camera);

BaseObject
renderer_create_textured_rectangle(f32 x, f32 y);
void
renderer_draw_textured_rectangle(BaseObject* objectToDraw, Shader* shader, Texture2D* texture, OrthographicCamera* camera);

RectangleArray 
renderer_rectangle_array_create(OrthographicCamera* camera);
void 
renderer_rectangle_array_draw(RectangleArray array);
static void
renderer_rectangle_array_destroy(RectangleArray array)
{
	graphics_vertex_array_destroy(&array.VAO);
}

static void
renderer_destroy_base_object(BaseObject* object)
{	
	graphics_vertex_array_destroy(&object->VertexArray);
}

static void
renderer_set_viewport(u32 width, u32 height)
{
  //OpenGL stuff
  glViewport(0, 0, width, height);
}

//0.2f, 0.345f, 0.456f, 1.0f
static void
renderer_clear(vec4 color)
{
  glClearColor(color[0], color[1], color[2], color[3]);
  glClear(GL_COLOR_BUFFER_BIT);
}

/*
  Batch renderers
*/

typedef struct QuadVertex
{
  vec3 Position;
  vec4 Color;
  vec2 TexturePosition;
  f32 TextureId;
} QuadVertex;

typedef struct Quad
{
  QuadVertex vertex[4];
} Quad;

#define MaxObjectToDraw 10000
#define MaxTextureSlots 32

#define QuadVertexElementCount (3 + 4 + 2 + 1)
#define QuadVerticesCount (4 * QuadVertexElementCount) 
#define SizeofQuadVertex (QuadVertexElementCount * sizeof(f32))
#define VerticesCount (MaxObjectToDraw * QuadVerticesCount)
#define IndicesCount (MaxObjectToDraw * 6)
#define VertexBufferSize (VerticesCount * sizeof(f32))

typedef struct BatchRenderer2DData
{
  u32 DataCount;
  u32 NextTextureIndex;
  f32 Data[VerticesCount];

  u32 IndexCount;
  u32 Indices[IndicesCount];

  VertexArray Vao;
  Shader Shader;
  Texture2D Textures[32];
} BatchRenderer2DData;

static void
fill_indices_array(u32* indices, u32 length)
{
    i32 i;
    u32 temp;
    for (i = 0, temp = 0; i < length; i += 6, temp += 4)
	{
	    indices[i]     = 0 + temp;
	    indices[i + 1] = 1 + temp;
	    indices[i + 2] = 2 + temp;
	    indices[i + 3] = 2 + temp;
	    indices[i + 4] = 3 + temp;
	    indices[i + 5] = 0 + temp;
	}
}

static void
fill_data_array(f32* destination, vec3 position, vec2 size, vec4 color, i32 textureId, u32 start_index)
{
    i32 i = start_index;
  
    destination[i++] = position[0];
	destination[i++] = position[1];
	destination[i++] = position[2];
	destination[i++] = color[0];
	destination[i++] = color[1];
	destination[i++] = color[2];
	destination[i++] = color[3];
	destination[i++] = 0;
	destination[i++] = 0;
	destination[i++] = (f32) textureId;
	
	destination[i++] = position[0];
	destination[i++] = position[1] + size[1];
	destination[i++] = position[2];
	destination[i++] = color[0];
	destination[i++] = color[1];
	destination[i++] = color[2];
	destination[i++] = color[3];
	destination[i++] = 0;
	destination[i++] = 1;
	destination[i++] = (f32) textureId;
	
	destination[i++] = position[0] + size[0];
	destination[i++] = position[1] + size[1];
	destination[i++] = position[2];
	destination[i++] = color[0];
	destination[i++] = color[1];
	destination[i++] = color[2];
	destination[i++] = color[3];
	destination[i++] = 1;
	destination[i++] = 1;
	destination[i++] = (f32) textureId;
	
	destination[i++] = position[0] + size[0];
	destination[i++] = position[1];
	destination[i++] = position[2];
	destination[i++] = color[0];
	destination[i++] = color[1];
	destination[i++] = color[2];
	destination[i++] = color[3];
	destination[i++] = 1;
	destination[i++] = 0;
	destination[i++] = (f32) textureId;
}

void
renderer_batch_init();

void
renderer_submit_rectangle(vec3 position, vec2 size, Texture2D* texture, Shader* shader, OrthographicCamera* camera);

void
renderer_submit_colored_rectangle(vec3 position, vec2 size, vec4 color);

void
renderer_flush(Shader* shader, OrthographicCamera* camera);

