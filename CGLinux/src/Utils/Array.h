#pragma once

#define MAX(x, y) ((x) >= (y) ? (x) : (y))

typedef struct buffer_header
{
    size_t length;
    size_t capacity;
    char array[0]; // [0] C99 only feature
} buffer_header;

/*
 	The macro offsetof() returns the offset of the field 
	member from the start of the structure type
	NOTE it's offset because we take 0 address memory 
	convert it to size_t type 
	#define offset(type, mem) (size_t) &(((type*)0)->mem)
*/

void* array_grow(const void* array, size_t new_len, size_t elem_size);

#define array_hdr(b) ((buffer_header*) ((char*)b - offsetof(buffer_header, array)))
#define array_len(b) ((b) ? array_hdr(b)->length : 0)
#define array_cap(b) ((b) ? array_hdr(b)->capacity : 0)
#define array_fits(b, n) (array_len(b) + (n) <= array_cap(b))
#define array_fit(b, n) (array_fits(b,n) ? 0 : ((b) = array_grow((b), array_len(b) + (n), sizeof(*b))))

#define array_push(b, v) (array_fit(b, 1), b[array_len(b)] = (v), array_hdr(b)->length++)
#define array_free(b) ((b) ? free(array_hdr(b)) : 0)

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