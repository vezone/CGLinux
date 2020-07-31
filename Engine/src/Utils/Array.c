#include "Array.h"

#include <stdlib.h>

void* array_grow(const void* array, size_t new_len, size_t elem_size)
{
	size_t new_cap = MAX(1 + 2 * array_cap(array), new_len);
	size_t new_size = offsetof(buffer_header, array) + new_cap*elem_size;
	buffer_header* new_hdr;
	if (array)
	{
		new_hdr = realloc(array_hdr(array), new_size); 
	}
	else
	{
		new_hdr = malloc(new_size);
		new_hdr->length = 0;
	}
	
	new_hdr->capacity = new_cap;
	return new_hdr->array;
}