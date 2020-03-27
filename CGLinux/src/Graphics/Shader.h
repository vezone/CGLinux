#pragma once

#include <glad/glad.h>
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

static void
graphics_shader_uniform1f(u32 shader, const char* uniformName, f32 v0)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform1f(location, v0);
}

static void
graphics_shader_uniform2f(u32 shader, const char* uniformName, f32 v0, f32 v1)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform2f(location, v0, v1);
}

static void
graphics_shader_uniform3f(u32 shader, const char* uniformName, f32 v0, f32 v1, f32 v2)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform3f(location, v0, v1, v2);
}

static void
graphics_shader_uniform4f(u32 shader, const char* uniformName, f32 v0, f32 v1, f32 v2, f32 v3)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform4f(location, v0, v1, v2, v3);
}


static void
graphics_shader_uniform1i(u32 shader, const char* uniformName, i32 v0)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform1i(location, v0);
}

static void
graphics_shader_uniform2i(u32 shader, const char* uniformName, i32 v0, i32 v1)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform2i(location, v0, v1);
}

static void
graphics_shader_uniform3i(u32 shader, const char* uniformName, i32 v0, i32 v1, i32 v2)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform3i(location, v0, v1, v2);
}

static void
graphics_shader_uniform4i(u32 shader, const char* uniformName, i32 v0, i32 v1, i32 v2, i32 v3)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform4i(location, v0, v1, v2, v3);
}

static void
graphics_shader_uniform1ui(u32 shader, const char* uniformName, u32 v0)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform1ui(location, v0);
}

static void
graphics_shader_uniform2ui(u32 shader, const char* uniformName, u32 v0, u32 v1)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform2ui(location, v0, v1);
}

static void
graphics_shader_uniform3ui(u32 shader, const char* uniformName, u32 v0, u32 v1, u32 v2)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform3ui(location, v0, v1, v2);
}

static void
graphics_shader_uniform4ui(u32 shader, const char* uniformName, u32 v0, u32 v1, u32 v2, u32 v3)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform4ui(location, v0, v1, v2, v3);
}


static void
graphics_shader_uniform1fv(u32 shader, const char* uniformName, i32 count, f32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform1fv(location, count, values);
}

static void
graphics_shader_uniform2fv(u32 shader, const char* uniformName, i32 count, f32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform2fv(location, count, values);
}

static void
graphics_shader_uniform3fv(u32 shader, const char* uniformName, i32 count, f32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform3fv(location, count,  values);
}

static void
graphics_shader_uniform4fv(u32 shader, const char* uniformName, i32 count, f32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform4fv(location, count, values);
}

static void
graphics_shader_uniform1iv(u32 shader, const char* uniformName, i32 count, i32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform4iv(location, count, values);
}

static void
graphics_shader_uniform2iv(u32 shader, const char* uniformName, i32 count, i32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform2iv(location, count, values);
}

static void
graphics_shader_uniform3iv(u32 shader, const char* uniformName, i32 count, i32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform3iv(location, count, values);
}

static void
graphics_shader_uniform4iv(u32 shader, const char* uniformName, i32 count, i32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform4iv(location, count, values);
}

static void
graphics_shader_uniform1uiv(u32 shader, const char* uniformName, i32 count, u32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform4uiv(location, count, values);
}

static void
graphics_shader_uniform2uiv(u32 shader, const char* uniformName, i32 count, u32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform2uiv(location, count, values);
}

static void
graphics_shader_uniform3uiv(u32 shader, const char* uniformName, i32 count, u32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform3uiv(location, count, values);
}

static void
graphics_shader_uniform4uiv(u32 shader, const char* uniformName, i32 count, u32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniform4uiv(location, count, values);
}

static void
graphics_shader_uniform_mat2(u32 shader, const char* uniformName, i32 count, i8 transpose, f32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniformMatrix2fv(location, count, transpose, values);
}

static void
graphics_shader_uniform_mat3(u32 shader, const char* uniformName, i32 count, i8 transpose, f32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniformMatrix3fv(location, count, transpose, values);
}

static void
graphics_shader_uniform_mat4(u32 shader, const char* uniformName, i32 count, i8 transpose, f32* values)
{
	i32 location = glGetUniformLocation(shader, uniformName);
	if (location >= 0)
		glUniformMatrix4fv(location, count, transpose, values);
}
