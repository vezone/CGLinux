#include <stdlib.h>

#include <glad/glad.h>
#include "graphics_buffer.h"

void graphics_buffer_layout_create(graphics_buffer_layout* layout, graphics_buffer_element* elements)
{
	int32 offset = 0;
	int32 length = varray_len(elements);
	for (graphics_buffer_element* it = elements; 
		it != (elements + length * sizeof(graphics_buffer_element)); 
		it++)
	{
		it->offset      = offset;
		offset 		   += it->size;
		layout->stride += it->size;
	}
	layout->elements = elements;
}

void graphics_vertex_buffer_create(graphics_vertex_buffer* buffer, float* vertices, uint32_t size)
{
	buffer->vertices = vertices;
	glGenBuffers(1, &(buffer->rendererID));
	glBindBuffer(GL_ARRAY_BUFFER, buffer->rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void graphics_vertex_buffer_bind(graphics_vertex_buffer* vertex_buffer)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->rendererID);
}

void graphics_vertex_buffer_unbind(graphics_vertex_buffer* vertex_buffer)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void graphics_index_buffer_create(graphics_index_buffer* buffer, uint32_t* indices, uint32_t count)
{
	buffer->count = count;
	buffer->indices = indices;
	glGenBuffers(1, &(buffer->rendererID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(indices), indices, GL_STATIC_DRAW);
}

void graphics_index_buffer_bind(graphics_index_buffer* index_buffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->rendererID);
}

void graphics_index_buffer_unbind(graphics_index_buffer* index_buffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
