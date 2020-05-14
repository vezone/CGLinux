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


/*
  Batch renderers
*/

#define VertexCount 10000000 
#define MaxVertices 6 * VertexCount
#define MaxIndices 6 * VertexCount
#define SizeofVertices MaxVertices * 6

typedef struct QuadVertex
{
  vec2 Position;
  vec4 Color;
} QuadVertex;

typedef struct Quad
{
  i8 IsSolidColor;
  QuadVertex vertex[4];
} Quad;

typedef struct ColoredBatchRenderer2DData
{
  u32 DataCount;
  f32 Data[MaxVertices];

  u32 IndexCount;
  u32 Indices[MaxIndices];

  VertexArray Vao;
  mat4 Transform;
} ColoredBatchRenderer2DData;

void
fill_indices_array(u32* indices, u32 length);

void
quad_fill_data_to_array(f32* destination, Quad* source, u32 start_index);

//NOTE(vez): we are not handle z axis for now
//size[0] - width
//size[1] - height
void
quad_vertex_create_color(Quad* quad, vec3 position, vec2 size, vec4 c11);

//NOTE(vez): we are not handle z axis for now
//size[0] - width
//size[1] - height
void
quad_vertex_create_gradient(Quad* quad, vec3 position, vec2 size, vec4 c11, vec4 c12, vec4 c22, vec4 c21);

void
color_renderer_batch_init();

void
color_renderer_submit_rectangle(vec3 position, vec2 size, i8 isSolid, vec4 c11, vec4 c12, vec4 c22, vec4 c21);

void
color_renderer_flush(Shader* shader, OrthographicCamera* camera);

