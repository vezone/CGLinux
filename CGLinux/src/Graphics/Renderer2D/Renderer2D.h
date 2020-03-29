#pragma once

#include "Utils/Types.h"
#include "Graphics/Buffer.h"
#include "Graphics/Renderer2D/OrthographicCamera.h"
#include "Graphics/Texture2D.h"
#include "cglm/cglm.h"

typedef struct GColor {
	f32 R;
	f32 G;
	f32 B;
	f32 A;
} GColor;

typedef struct TriangleGeometry {
	f32 A[2];
	f32 B[2];
	f32 C[2];
} TriangleGeometry;

typedef struct Triangle {
	u32 Shader;
	VertexArray VAO;
    TriangleGeometry Geometry;
	GColor Color;
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
	GColor Color;
    OrthographicCamera* Camera;
} Rectangle;

typedef struct TexturedRectangle {
	u32 Shader;
	VertexArray VAO;
	Texture2D Texture;
    RectangleGeometry Geometry;
    OrthographicCamera* Camera;
} TexturedRectangle;

typedef struct RectangleArray {
	u32 Shader;
	VertexArray VertexArray;
    OrthographicCamera* Camera;
} RectangleArray;

Triangle 
renderer_triangle_create(TriangleGeometry geometry, GColor color, mat4 transform, OrthographicCamera* camera);
static void
renderer_triangle_destroy(Triangle triangle)
{
	graphics_vertex_array_destroy(&triangle.VAO);
}
void
renderer_triangle_draw(Triangle triangle);

Rectangle 
renderer_rectangle_create(RectangleGeometry geometry, GColor color, OrthographicCamera* camera);
void 
renderer_rectangle_set_shader_default(Rectangle rectangle);
void 
renderer_rectangle_draw(Rectangle rectangle);

TexturedRectangle
renderer_create_textured_rectangle(RectangleGeometry geometry, const char* texturePath, OrthographicCamera* camera);
void
renderer_textured_rectangle_draw(TexturedRectangle rectangle);

RectangleArray 
renderer_rectangle_array_create(OrthographicCamera* camera);
void 
renderer_rectangle_array_draw(RectangleArray array);
