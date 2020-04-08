#pragma once

#include "Utils/Types.h"
#include "Graphics/Buffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Renderer2D/OrthographicCamera.h"
#include "Graphics/Texture2D.h"
#include "cglm/cglm.h"


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

typedef struct Triangle {
	u32 Shader;
	VertexArray VAO;
	mat4 Transform;
    OrthographicCamera* Camera;
} Triangle;

typedef struct RectangleGeometry {
	f32 TopX;
	f32 TopY;
	f32 Width;
	f32 Height;
} RectangleGeometry;

typedef struct Rectangle {
	u32 Shader;
	VertexArray VAO;
    RectangleGeometry Geometry;
	mat4 Transform;
    OrthographicCamera* Camera;
} Rectangle;

typedef struct TexturedRectangle {
	u32 Shader;
	VertexArray VAO;
	Texture2D Texture;
    RectangleGeometry Geometry;
	vec3 Position;
	vec2 Size;
	mat4 Transform;
    OrthographicCamera* Camera;
} TexturedRectangle;

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
renderer_create_colored_rectangle();
void 
renderer_draw_colored_rectangle(BaseObject* objectToDraw, Shader* shader, vec4 color, OrthographicCamera* camera);

BaseObject
renderer_create_textured_rectangle();
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
