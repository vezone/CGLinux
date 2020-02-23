#pragma once

#include "Utils/Types.h"
#include "Graphics/Buffer.h"
#include <Graphics/Renderer2D/OrthographicCamera.h>

typedef struct GColor {
	f32 R;
	f32 G;
	f32 B;
	f32 A;
} GColor;

typedef struct GPosition {
	f32 TopX;
	f32 TopY;
	f32 Width;
	f32 Height;
} GPosition;

typedef struct Quad {
	u32 Shader;
	VertexArray VAO;
    GPosition Position;
	GColor Color;
    OrthographicCamera* camera;
} Quad;

typedef struct QuadArray {
	u32 Shader;
	VertexArray VertexArray;
    OrthographicCamera* Camera;
} QuadArray;

Quad renderer_quad_create(GPosition position, GColor color, u32 shared_shader, OrthographicCamera* camera);
void renderer_quad_set_shader_default(Quad quad);
void renderer_quad_draw(Quad quad);

QuadArray renderer_quad_array(u32 shader, OrthographicCamera* camera);
void renderer_quad_array_draw(QuadArray array);
