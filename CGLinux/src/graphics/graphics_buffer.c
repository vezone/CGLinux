#include <stdlib.h>

#include <glad/glad.h>
#include "graphics_buffer.h"

void 
graphics_vertex_buffer_create(graphics_vertex_buffer* buffer, float* vertices, uint32 size)
{
	buffer->Vertices = vertices;
	glGenBuffers(1, &(buffer->RendererID));
	glBindBuffer(GL_ARRAY_BUFFER, buffer->RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void 
graphics_vertex_buffer_bind(graphics_vertex_buffer* vertex_buffer)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->RendererID);
}

void 
graphics_vertex_buffer_unbind(graphics_vertex_buffer* vertex_buffer)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void 
graphics_index_buffer_create(graphics_index_buffer* buffer, uint32* indices, uint32 count)
{
	buffer->Count = count;
	buffer->Indices = indices;
	glGenBuffers(1, &(buffer->RendererID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(indices), indices, GL_STATIC_DRAW);
}

void 
graphics_index_buffer_bind(graphics_index_buffer* index_buffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->RendererID);
}

void 
graphics_index_buffer_unbind(graphics_index_buffer* index_buffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void graphics_vertex_array_create(graphics_vertex_array* va, uint32 size, float* vertices, data_type type) 
{
	va->Element.IsNormilized = 0;
	va->Element.Size = sizeof(vertices);
	va->Element.Type = type;
	va->VertexAttribArrayID = vertex_array_count;
	va->VertexBuffer.Vertices = vertices;
	glGenBuffers(1, &(va->VertexBuffer.RendererID));
	glBindBuffer(GL_ARRAY_BUFFER, va->VertexBuffer.RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glCreateVertexArrays(1, &(va->RendererID));

	++vertex_array_count;
}

void graphics_vertex_array_bind(graphics_vertex_array* va) 
{
	glBindBuffer(GL_ARRAY_BUFFER, va->VertexBuffer.RendererID);
	glEnableVertexAttribArray(va->VertexAttribArrayID);
	glVertexAttribPointer(va->VertexAttribArrayID, 3, GL_FLOAT, 0, data_type_get_size(va->Element.Type), (void*)0);
	glBindVertexArray(va->RendererID);
}

void graphics_vertex_array_unbind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}