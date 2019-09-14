#pragma once

#pragma once

#include "../vlib/core/vtypes.h"
#include "../vlib/core/varray.h"

typedef enum data_type
{
	data_type_none = 0,
	data_type_float1, data_type_float2, data_type_float3, data_type_float4,
	data_type_int1, data_type_int2, data_type_int3, data_type_int4
} data_type;

static uint32 data_type_get_size(data_type type)
{
	switch (type)
	{
		case data_type_float1: return 4;
		case data_type_float2: return 4 * 2;
		case data_type_float3: return 4 * 3;
		case data_type_float4: return 4 * 4;
		case data_type_int1: return 4;
		case data_type_int2: return 4 * 2;
		case data_type_int3: return 4 * 3;
		case data_type_int4: return 4 * 4; 
	}
	//for debug purpose
	asserts(0, "Unknown data type!");
}

static uint32 data_type_get_count(data_type type)
{
	switch (type)
	{
		case data_type_float1: return 1;
		case data_type_float2: return 2;
		case data_type_float3: return 3;
		case data_type_float4: return 4;
		case data_type_int1: return 1;
		case data_type_int2: return 2;
		case data_type_int3: return 3;
		case data_type_int4: return 4; 
	}
	//for debug purpose
	asserts(0, "Unknown data type!");
}

typedef struct graphics_buffer_element
{
	int8 is_normilized;
	data_type type;
	int32 size;
	int32 offset;
} graphics_buffer_element;

typedef struct graphics_buffer_layout
{
	int32 stride;
	graphics_buffer_element* elements;
} graphics_buffer_layout;

void graphics_buffer_layout_create(graphics_buffer_layout* layout, graphics_buffer_element* elements);

typedef struct graphics_vertex_buffer
{
	float* vertices;
	uint32_t rendererID;
	graphics_buffer_layout* layout;
} graphics_vertex_buffer;

void graphics_vertex_buffer_create(graphics_vertex_buffer* buffer, float* vertices, uint32_t size);
void graphics_vertex_buffer_bind(graphics_vertex_buffer* vertex_buffer);
void graphics_vertex_buffer_unbind(graphics_vertex_buffer* vertex_buffer);

typedef struct graphics_index_buffer
{
	uint32* indices;
	uint32 rendererID;
	uint32 count;
} graphics_index_buffer;

void graphics_index_buffer_create(graphics_index_buffer* buffer, uint32_t* indices, uint32_t size);
void graphics_index_buffer_bind(graphics_index_buffer* index_buffer);
void graphics_index_buffer_unbind(graphics_index_buffer* index_buffer);