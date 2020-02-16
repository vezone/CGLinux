#pragma once 

#include "../vlib/core/vtypes.h"

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
	const char* vertex_shader;
	const char* fragment_shader;
} graphics_shader_source;

static void 
file_write_string(char* file_path, char* data, int32 len);

static const char* 
file_read_string(const char* file_path);

graphics_shader_source 
graphics_shader_load(const char* shader_path);

uint32 
graphics_shader_compile(graphics_shader_source source);

void 
graphics_shader_delete(uint32 renderId);

void 
graphics_shader_bind(uint32 renderId);

void 
graphics_shader_unbind();