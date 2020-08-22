#include "Renderer2D.h"

#include <glad/glad.h>
#include <Graphics/Shader.h>
#include <Utils/Logger.h>
#include <Utils/Array.h>

BaseObject
renderer_create_colored_triangle()
{
    f32 vertices[] = {
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
    f32 vertices[] = {
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

    f32 vertices[] = {
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
    .IndexCount = 0
};
static Renderer2DStatistics* g_Statistics;

static i32 TextureIndices[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
static vec3 BaseVectorPositions[4] = {
    { -0.5f, -0.5f, 0.0f }, /* 0 0 */
    { -0.5f,  0.5f, 0.0f }, /* 0 1 */
    {  0.5f,  0.5f, 0.0f }, /* 1 1 */
    {  0.5f, -0.5f, 0.0f }  /* 1 0 */
};

force_inline void
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

force_inline void
fill_data_array(f32* destination, vec3 position, vec2 size, vec4 color, i32 textureId, u32 isTextured, u32 startIndex)
{
    i32 i = startIndex;

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
    destination[i++] = (f32) isTextured;

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
    destination[i++] = (f32) isTextured;

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
    destination[i++] = (f32) isTextured;

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
    destination[i++] = (f32) isTextured;

    ++g_Statistics->RectanglesCount;
}

force_inline void
fill_rotated_data_array(f32* destination, vec3 positionsArray[4], vec4 color, i32 textureId, u32 isTextured, u32 startIndex)
{
    i32 i = startIndex;

    destination[i++] = positionsArray[0][0];
    destination[i++] = positionsArray[0][1];
    destination[i++] = positionsArray[0][2];
    destination[i++] = color[0];
    destination[i++] = color[1];
    destination[i++] = color[2];
    destination[i++] = color[3];
    destination[i++] = 0;
    destination[i++] = 0;
    destination[i++] = (f32) textureId;
    destination[i++] = (f32) isTextured;

    destination[i++] = positionsArray[1][0];
    destination[i++] = positionsArray[1][1];
    destination[i++] = positionsArray[1][2];
    destination[i++] = color[0];
    destination[i++] = color[1];
    destination[i++] = color[2];
    destination[i++] = color[3];
    destination[i++] = 0;
    destination[i++] = 1;
    destination[i++] = (f32) textureId;
    destination[i++] = (f32) isTextured;

    destination[i++] = positionsArray[2][0];
    destination[i++] = positionsArray[2][1];
    destination[i++] = positionsArray[2][2];
    destination[i++] = color[0];
    destination[i++] = color[1];
    destination[i++] = color[2];
    destination[i++] = color[3];
    destination[i++] = 1;
    destination[i++] = 1;
    destination[i++] = (f32) textureId;
    destination[i++] = (f32) isTextured;

    destination[i++] = positionsArray[3][0];
    destination[i++] = positionsArray[3][1];
    destination[i++] = positionsArray[3][2];
    destination[i++] = color[0];
    destination[i++] = color[1];
    destination[i++] = color[2];
    destination[i++] = color[3];
    destination[i++] = 1;
    destination[i++] = 0;
    destination[i++] = (f32) textureId;
    destination[i++] = (f32) isTextured;

    ++g_Statistics->RectanglesCount;
}

force_inline void
texture_list_set_immutable(TextureList* list, Texture2D* texture)
{
    list->Textures[list->StartIndex++] = *texture;
}

force_inline i8
texture_list_is_full(TextureList* list)
{
    return list->NextTextureIndex >= list->MaxTextureSlot;
}

force_inline i32
texture_list_contains(TextureList* list, Texture2D* texture)
{
    i8 isAlreadyInList = -1;
    i32 i;
    u32 id;

    for (i = 1; i < list->NextTextureIndex; i++)
    {
        id = list->Textures[i].RendererID;
        if (id == texture->RendererID)
        {
            return i;
        }
    }

    return isAlreadyInList;
}

force_inline void
texture_list_add(TextureList* list, Texture2D* texture, i32 textureId)
{
    list->Textures[textureId] = *texture;
    ++list->NextTextureIndex;
}

force_inline void
texture_list_bind(TextureList* list)
{
    i32 i;
    for (i = 0; i < list->NextTextureIndex; i++)
    {
        graphics_texture2d_bind(&(list->Textures[i]), i);
    }
}

void
renderer_batch_init(Renderer2DStatistics* statistics, Shader* shader, Texture2D* whiteTexture, OrthographicCamera* camera)
{
    VertexBuffer vbo = {};
    IndexBuffer ibo = {};
    g_Statistics = statistics;

    g_Shader = shader;
    g_Camera = camera;

    graphics_vertex_buffer_allocate(&vbo, VertexBufferSize);
    graphics_vertex_buffer_bind(&vbo);
    graphics_vertex_buffer_add_layout(&vbo, 0, Float3);
    graphics_vertex_buffer_add_layout(&vbo, 0, Float4);
    graphics_vertex_buffer_add_layout(&vbo, 0, Float2);
    graphics_vertex_buffer_add_layout(&vbo, 0, Float1);
    graphics_vertex_buffer_add_layout(&vbo, 0, Float1);

    fill_indices_array(g_RendererData.Indices, IndicesCount);
    graphics_index_buffer_create(&ibo, g_RendererData.Indices, IndicesCount);
    graphics_index_buffer_bind(&ibo);

    graphics_vertex_array_create(&g_RendererData.Vao);
    graphics_vertex_array_add_vbo(&g_RendererData.Vao, vbo);
    graphics_vertex_array_add_ibo(&g_RendererData.Vao, ibo);
    graphics_vertex_array_bind(&g_RendererData.Vao);
    g_RendererData.List = (TextureList) {
        .StartIndex = 0,
        .MaxTextureSlot = 32,
        .NextTextureIndex = 1
    };
    texture_list_set_immutable(&g_RendererData.List, whiteTexture);
}

void
renderer_submit_rectangle(vec3 position, vec2 size, Texture2D* texture)
{
    i32 textureId;
    vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

    i8 isTextureListFull = texture_list_is_full(&g_RendererData.List);
    if (!isTextureListFull &&
        ((g_RendererData.DataCount + QuadVerticesCount) < VerticesCount))
    {
        textureId = texture_list_contains(&g_RendererData.List, texture);
        if (textureId == -1)
        {
            textureId = g_RendererData.List.NextTextureIndex;
            texture_list_add(&g_RendererData.List, texture, textureId);
            //g_RendererData.Textures[textureId] = *texture;
            //++g_RendererData.NextTextureIndex;
        }
    }
    else
    {
        renderer_flush();
        textureId = g_RendererData.List.StartIndex;
        //textureId = 1;
        texture_list_add(&g_RendererData.List, texture, textureId);
        //g_RendererData.Textures[textureId] = *texture;
        //++g_RendererData.NextTextureIndex;
    }

    fill_data_array(g_RendererData.Data, position, size, color, textureId, 1, g_RendererData.DataCount);
    g_RendererData.DataCount  += QuadVerticesCount;
    g_RendererData.IndexCount += 6;
}

void
renderer_submit_rotated_rectangle(vec3 position, vec2 size, f32 angle, Texture2D* texture)
{
    i32 textureId;
    vec3 rotatedPosVec;
    vec3 scaleVec = { 0.0f, 0.0f, 1.0f };
    vec2 nullSizeVec = {0.0f, 0.0f};
    vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
    mat4 transformMat = GLM_MAT4_IDENTITY_INIT;
    mat4 translationMat = GLM_MAT4_IDENTITY_INIT;
    mat4 rotationMat = GLM_MAT4_IDENTITY_INIT;
    mat4 scaleMat = GLM_MAT4_IDENTITY_INIT;

    i8 isTextureListFull = texture_list_is_full(&g_RendererData.List);
    if (!isTextureListFull &&
        ((g_RendererData.DataCount + QuadVerticesCount) < VerticesCount))
    {
        textureId = texture_list_contains(&g_RendererData.List, texture);
        if (textureId == -1)
        {
            textureId = g_RendererData.List.NextTextureIndex;
            texture_list_add(&g_RendererData.List, texture, textureId);
        }
    }
    else
    {
        renderer_flush();
        textureId = g_RendererData.List.StartIndex;
        texture_list_add(&g_RendererData.List, texture, textureId);
    }

    glm_translate(translationMat, position);
    glm_rotate_z(rotationMat, glm_rad(angle), rotationMat);

    scaleVec[0] = size[0];
    scaleVec[1] = size[1];
    glm_scale(scaleMat, scaleVec);

    glm_mat4_mulN((mat4*[]) {&translationMat, &rotationMat, &scaleMat}, 3, transformMat);

    vec3 positionsArray[4];
    glm_mat4_mulv3(transformMat, BaseVectorPositions[0], 1.0f, positionsArray[0]);
    glm_mat4_mulv3(transformMat, BaseVectorPositions[1], 1.0f, positionsArray[1]);
    glm_mat4_mulv3(transformMat, BaseVectorPositions[2], 1.0f, positionsArray[2]);
    glm_mat4_mulv3(transformMat, BaseVectorPositions[3], 1.0f, positionsArray[3]);

    fill_rotated_data_array(g_RendererData.Data, positionsArray, color, textureId, 1, g_RendererData.DataCount);
    g_RendererData.DataCount  += QuadVerticesCount;
    g_RendererData.IndexCount += 6;
}

void
renderer_submit_colored_rectangle(vec3 position, vec2 size, vec4 color)
{
    fill_data_array(g_RendererData.Data, position, size, color, 0, 0, g_RendererData.DataCount);
    g_RendererData.DataCount  += QuadVerticesCount;
    g_RendererData.IndexCount += 6;
}

void
renderer_submit_colored_rotated_rectangle(vec3 position, vec2 size, vec4 color, f32 angle)
{
    mat4 transformMat = GLM_MAT4_IDENTITY_INIT;
    mat4 translationMat = GLM_MAT4_IDENTITY_INIT;
    mat4 rotationMat = GLM_MAT4_IDENTITY_INIT;
    mat4 scaleMat = GLM_MAT4_IDENTITY_INIT;
    vec3 scaleVec = { 0.0f, 0.0f, 1.0f };
    vec2 nullSizeVec = {0.0f, 0.0f};
    vec3 rotatedPosVec;

    glm_translate(translationMat, position);
    glm_rotate_z(rotationMat, glm_rad(angle), rotationMat);

    scaleVec[0] = size[0];
    scaleVec[1] = size[1];
    glm_scale(scaleMat, scaleVec);

    glm_mat4_mulN((mat4*[]) {&translationMat, &rotationMat, &scaleMat}, 3, transformMat);

    vec3 positionsArray[4];
    glm_mat4_mulv3(transformMat, BaseVectorPositions[0], 1.0f, positionsArray[0]);
    glm_mat4_mulv3(transformMat, BaseVectorPositions[1], 1.0f, positionsArray[1]);
    glm_mat4_mulv3(transformMat, BaseVectorPositions[2], 1.0f, positionsArray[2]);
    glm_mat4_mulv3(transformMat, BaseVectorPositions[3], 1.0f, positionsArray[3]);

    fill_rotated_data_array(g_RendererData.Data, positionsArray, color, 0, 0, g_RendererData.DataCount);
    g_RendererData.DataCount  += QuadVerticesCount;
    g_RendererData.IndexCount += 6;
}

void
renderer_flush()
{
    u32 size;

    graphics_shader_bind(g_Shader);
    graphics_vertex_array_bind(&g_RendererData.Vao);

    texture_list_bind(&g_RendererData.List);

    PRINT_ONESF(GDEBUG, "DataCount: %d\n", g_RendererData.DataCount);

    size = g_RendererData.DataCount * sizeof(f32);
    graphics_vertex_buffer_set_data(
        g_RendererData.Vao.VertexBuffer,
        g_RendererData.Data, size);

    graphics_shader_set_mat4(g_Shader,
                             "u_ViewProjection", 1, 0,
                             g_Camera->ViewProjectionMatrix[0]);
    graphics_shader_set_int1(g_Shader, "u_Textures", g_RendererData.List.NextTextureIndex, TextureIndices);

    glDrawElements(GL_TRIANGLES,
                   g_RendererData.IndexCount,
                   GL_UNSIGNED_INT,
                   NULL);

    g_RendererData.DataCount  = 0;
    g_RendererData.IndexCount = 0;
    g_RendererData.List.NextTextureIndex = 1;

    ++g_Statistics->DrawCalls;
}
