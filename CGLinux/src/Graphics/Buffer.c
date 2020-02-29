#include "Buffer.h"

#include <stdlib.h>
#include <glad/glad.h>
#include "Utils/Array.h"

void 
graphics_vertex_buffer_create(VertexBuffer* buffer, float* vertices, uint32_t size, DataType type)
{
	buffer->Vertices = vertices;
	glGenBuffers(1, &(buffer->RendererID));
	glBindBuffer(GL_ARRAY_BUFFER, buffer->RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	buffer->Element.IsNormilized = 0;
	buffer->Element.Size = size;
	buffer->Element.Type = type;
	buffer->Vertices = vertices;
}

void 
graphics_vertex_buffer_bind(VertexBuffer* vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo->RendererID);
}

void 
graphics_vertex_buffer_unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void 
graphics_index_buffer_create(IndexBuffer* buffer, uint32* indices, uint32 count)
{
	buffer->Count = count;
	buffer->Indices = indices;
	glGenBuffers(1, &(buffer->RendererID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
}

void 
graphics_index_buffer_bind(IndexBuffer* ibo)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->RendererID);
}

void 
graphics_index_buffer_unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void graphics_vertex_array_create(VertexArray* va) 
{
	glCreateVertexArrays(1, &(va->RendererID));
}

void graphics_vertex_array_add_vbo(VertexArray* va, VertexBuffer vbo)
{
	va->VertexBuffer = &vbo;
	glBindVertexArray(va->RendererID);
	
	glBindBuffer(GL_ARRAY_BUFFER, va->VertexBuffer->RendererID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
		data_type_get_count(va->VertexBuffer->Element.Type), 
		GL_FLOAT, 
		va->VertexBuffer->Element.IsNormilized, 
		data_type_get_size(va->VertexBuffer->Element.Type), 
		(void*)0);
}

void graphics_vertex_array_add_vbos(VertexArray* va, VertexBuffer* vbos)
{
	va->VertexBuffer = vbos;
	glBindVertexArray(va->RendererID);
	
	for (i32 i = 0; i < array_len(vbos); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, va->VertexBuffer[i].RendererID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(va->VertexBuffer[i].RendererID,
			data_type_get_count(va->VertexBuffer[i].Element.Type), 
			GL_FLOAT, 
			va->VertexBuffer[i].Element.IsNormilized, 
			data_type_get_size(va->VertexBuffer[i].Element.Type), 
			(void*)&va->VertexBuffer[i].Element.Size);
	}
}

void graphics_vertex_array_add_ibo(VertexArray* va, IndexBuffer ibo)
{
	va->IndexBuffer = ibo;
	glBindVertexArray(va->RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.RendererID);
}

void graphics_vertex_array_bind(VertexArray* va) 
{
	glBindVertexArray(va->RendererID);
}

void graphics_vertex_array_unbind() 
{
	glBindVertexArray(0);
}