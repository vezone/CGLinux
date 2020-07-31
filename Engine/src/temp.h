#ifndef TEMP
#define TEMP

#include "Utils/Types.h"

#define OffsetOf(type, member) (i64) &(((type*)0)->member)

typedef struct Anon
{
    i8 Flag;
    char Name[12];
    f32 Position[3];
    i64 BigFlag;
} Anon;

#define CSTRING_FILL(buf, string) { i32 i = 0; char c; while ((c = string[i]) != '\0') { buf[i++] = c; } }

#define STRING_FILL(buf, string) { while(*buf++ = *string++); }

typedef struct AllocationHeader AllocationHeader;

//40 bytes total
typedef struct AllocationHeader
{
    i8 IsFree; //**** ***1
    i64 BytesAllocated; //1111 1111
    AllocationHeader* Prev; //1111 1111
    AllocationHeader* Next; //1111 1111
    void* Allocated; //1111 1111
} AllocationHeader;

void* MemoryPool;
i64 Offset;
i64 AllocationSize;
i64 AllocationsCount;

AllocationHeader* FirstHeader;
AllocationHeader* LastHeader;

void bies_allocator_init();
void* bies_allocate(i32 size);
void bies_allocator_show();
void bies_allocator_test();

void imgui_test(void);

#endif
