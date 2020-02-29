#pragma once 

#include "Utils/Types.h"

#define ISSHADERDEBUG 0
#define ISSHADERLOG 1

#if ISSHADERDEBUG == 1
	#define SHADERDEBUG(...) printf(__VA_ARGS__)
#else
	#define SHADERDEBUG(...)
#endif

#if ISSHADERLOG == 1
	#define SHADERLOG(...) printf(__VA_ARGS__)
#else
	#define SHADERLOG(...)
#endif

typedef struct graphics_shader_source
{
	char* name;
	const char* vertex_shader;
	const char* fragment_shader;
} graphics_shader_source;

static void 
file_write_string(char* file_path, char* data, i32 len);

static const char* 
file_read_string(const char* file_path);

graphics_shader_source 
graphics_shader_load(const char* shader_path);

u32 
graphics_shader_compile(graphics_shader_source source);

void 
graphics_shader_delete(u32 renderId);

void 
graphics_shader_bind(u32 renderId);

void 
graphics_shader_unbind();

void
graphics_shader_delete_collection();