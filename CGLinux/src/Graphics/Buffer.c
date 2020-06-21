#include "Buffer.h"

#include <stdlib.h>
#include "Utils/Array.h"
#include "Utils/Logger.h"

static void
buffer_element_print(BufferElement element)
{
	BUFFERDEBUG("Size: %d, Count: %d, Offset: %d\n", 
       element.Size, element.Count, element.Offset);
}

void 
graphics_vertex_buffer_create(VertexBuffer* buffer, f32* vertices, u32 size)
{
  GLCheck(glGenBuffers(1, &(buffer->RendererID)));
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, buffer->RendererID));
  GLCheck(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
  
  buffer->Elements = NULL;
  buffer->Vertices = vertices;
}

void
graphics_vertex_buffer_allocate(VertexBuffer* buffer, u32 size)
{
  GLCheck(glGenBuffers(1, &(buffer->RendererID)));
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, buffer->RendererID));
  GLCheck(glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW));
  
  buffer->Elements = NULL;
  buffer->Vertices = NULL;
}


static void
stride_update(VertexBuffer* buffer)
{
  //0 12 24
  i32 i;
  i32 offset;
  i32 buffer_elements_length;

  offset = 0;
  buffer->Stride = 0;
  
  // o: 0, stride: 12
  // o: 12, stride: 24
  buffer_elements_length = array_len(buffer->Elements);
  for (i = 0; i < buffer_elements_length; i++)
  {
      buffer->Elements[i].Offset = offset;
      offset += buffer->Elements[i].Size;
      buffer->Stride += buffer->Elements[i].Size;
  }
}

void
graphics_vertex_buffer_add_layout(VertexBuffer* buffer, i8 isNormalized, DataType type)
{
  BufferElement element = {
      .IsNormilized = isNormalized,
	  .Type = type,
	  .Size = data_type_get_size(type),
	  .Count = data_type_get_count(type)
  };

  array_push(buffer->Elements, element);
  stride_update(buffer);
}

void 
graphics_vertex_buffer_bind(VertexBuffer* vbo)
{
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, vbo->RendererID));
}

void 
graphics_vertex_buffer_unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void 
graphics_index_buffer_create(IndexBuffer* buffer, u32* indices, u32 count)
{
  buffer->Count = count;
  buffer->Indices = indices;
  GLCheck(glGenBuffers(1, &(buffer->RendererID)));
  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->RendererID));
  GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW));
}

void 
graphics_index_buffer_bind(IndexBuffer* ibo)
{
  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->RendererID));
}

void 
graphics_index_buffer_unbind()
{
  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void graphics_vertex_array_create(VertexArray* va) 
{
  GLCheck(glCreateVertexArrays(1, &(va->RendererID)));
}

void graphics_vertex_array_add_vbo(VertexArray* va, VertexBuffer vbo)
{
  va->VertexBuffer = &vbo;
    
  GLCheck(glBindVertexArray(va->RendererID));
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, va->VertexBuffer->RendererID));
  BUFFERDEBUG("Stride: %d\n", vbo.Stride);

  BufferElement* layout = vbo.Elements;
  for (i32 i = 0; i < array_len(layout); i++)
  {
      BufferElement element = layout[i];
               
      buffer_element_print(element);
		
      GLCheck(glEnableVertexAttribArray(i));
      GLCheck(glVertexAttribPointer(i, element.Count, GL_FLOAT, element.IsNormilized, vbo.Stride, (const void*)element.Offset));
   }
}

void graphics_vertex_array_add_ibo(VertexArray* va, IndexBuffer ibo)
{
  va->IndexBuffer = ibo;
  GLCheck(glBindVertexArray(va->RendererID));
  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.RendererID));
}

void graphics_vertex_array_bind(VertexArray* va) 
{
  GLCheck(glBindVertexArray(va->RendererID));
}

void graphics_vertex_array_unbind()
{
  GLCheck(glBindVertexArray(0));
}
