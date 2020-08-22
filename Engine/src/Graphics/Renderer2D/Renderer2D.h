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

BaseObject renderer_create_colored_triangle();
void renderer_draw_colored_triangle(BaseObject* objectToDraw, Shader* shader, vec4 color, OrthographicCamera* camera);

BaseObject renderer_create_colored_rectangle(f32 x1, f32 x2, f32 y1, f32 y2);
void renderer_draw_colored_rectangle(BaseObject* objectToDraw, Shader* shader, vec4 color, OrthographicCamera* camera);

BaseObject renderer_create_textured_rectangle(f32 x, f32 y);
void renderer_draw_textured_rectangle(BaseObject* objectToDraw, Shader* shader, Texture2D* texture, OrthographicCamera* camera);

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
#define MaxObjectToDraw (i64)10000
#define MaxTextureSlots 32

#define QuadVertexElementCount (3 + 4 + 2 + 1 + 1)
#define QuadVerticesCount (4 * QuadVertexElementCount)
#define SizeofQuadVertex (QuadVertexElementCount * sizeof(f32))
#define VerticesCount (MaxObjectToDraw * QuadVerticesCount)
#define IndicesCount (MaxObjectToDraw * 6)
#define VertexBufferSize (VerticesCount * sizeof(f32))

typedef struct Renderer2DStatistics
{
    u32 DrawCalls;
    u32 RectanglesCount;
} Renderer2DStatistics;

force_inline void
renderer_reset_statistics(Renderer2DStatistics* statistics)
{
    statistics->DrawCalls = 0;
    statistics->RectanglesCount = 0;
}

typedef struct TextureList
{
    u32 MaxTextureSlot;
    u32 NextTextureIndex;
    u32 StartIndex;
    Texture2D Textures[32];
} TextureList;

typedef struct BatchRenderer2DData
{
    u32 DataCount;
    //u32 NextTextureIndex;
    u32 IndexCount;
    VertexArray Vao;
    Shader Shader;
    //Texture2D Textures[32];
    TextureList List;
    u32 Indices[IndicesCount];
    f32 Data[VerticesCount];
} BatchRenderer2DData;

void renderer_batch_init(Renderer2DStatistics* statistics, Shader* shader, Texture2D* whiteTexture, OrthographicCamera* camera);

void renderer_submit_rectangle(vec3 position, vec2 size, Texture2D* texture);
void renderer_submit_rotated_rectangle(vec3 position, vec2 size, f32 angle, Texture2D* texture);
void renderer_submit_colored_rectangle(vec3 position, vec2 size, vec4 color);
void renderer_submit_colored_rotated_rectangle(vec3 position, vec2 size, vec4 color, f32 angle);

void renderer_flush();

