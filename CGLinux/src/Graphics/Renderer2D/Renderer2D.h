#pragma once

#include <cglm/cglm.h>
#include "Graphics/Renderer2D/OrthographicCamera.h"
#include "Graphics/graphics_buffer.h"
#include "Graphics/graphics_shader.h"
#include "Utils/Types.h"

typedef struct RotationData {
	f32 Angle;
	mat4 Matrix;
	vec3 Axis;
} RotationData;

typedef struct RenderData {
	u32 Shader;
	VertexArray VertexArray;
	RotationData Rotation;
	OrthographicCamera* Camera;
} RenderData;

#define RENDER_DATA_PRINT(renderData) render_data_print(renderData, #renderData)

void
render_data_print(RenderData renderData, const char* caller);

RenderData
render_data_create(const char* shader_path, f32 vertices[9], OrthographicCamera* camera);

void
render_data_render(RenderData* renderData);