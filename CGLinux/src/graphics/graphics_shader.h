#pragma once 

#include <glad/glad.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../vlib/core/vtypes.h"
#include "../vlib/core/vstring.h"

static void file_write_string(char* file_path, char* data, int len)
{
	FILE* file;
	file = fopen(file_path, "w");
	fwrite(data, 1, len, file);
	fclose(file);
}

static const char* file_read_string(const char* file_path)
{
	FILE* file;
	file = fopen(file_path, "r");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		long file_length = (ftell(file));
		fseek(file, 0, SEEK_SET);
		char* result = (char*)malloc((file_length + 1) * sizeof(char));
		memset(result, '\0', (file_length + 1));
		fread(result, sizeof(char), (file_length - 1), file);
		result[file_length] = '\0';
		fclose(file);
		return((const char*)result);
	}
	return("file_open_error");
}

typedef struct {
	const char* vertex_shader;
	const char* fragment_shader;
} graphics_shader_source;


graphics_shader_source graphics_shader_load(
	const char* shader_path)
{
	const char* shader_source = file_read_string(shader_path);
	//printf("source:\n%s\n",shader_source);
	if (vstring_compare(shader_source, "file_open_error"))
	{
		asserts(0, BRIGHTRED("shader file open error!"));
	}
	int32 vertex_index   = vstring_index_of_string(shader_source, "#vertex shader");
	int32 fragment_index = vstring_index_of_string(shader_source, "#fragment shader");

	assert(vertex_index >=  0);
	assert(fragment_index >= 0);

	const char* vertex_shader_source = 
		vstring_substring_range(shader_source, 
			vertex_index + vstring_length("#vertex shader") + 1, fragment_index);
	printf(GREEN("%s"), vertex_shader_source);
	//FIXME: shader_source.length != real_shader_source.length
	const char* fragment_shader_source = 
		vstring_substring(shader_source, fragment_index + vstring_length("#fragment shader")+2);
	printf(GREEN("%s"), fragment_shader_source);

	assert(vstring_length(vertex_shader_source) > 0);
	assert(vstring_length(fragment_shader_source) > 0);
	
	return (graphics_shader_source) { 
		(const char*) vertex_shader_source, 
		(const char*) fragment_shader_source };
}

uint32 graphics_shader_compile(graphics_shader_source source)
{
	uint32 vertex_shader_id;
	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

	printf("Compiling vertex shader\n");
	glShaderSource(vertex_shader_id, 1, &source.vertex_shader, 0);
	glCompileShader(vertex_shader_id);

	int32 result = GL_FALSE;
	int32 info_log_length;
	glGetShaderiv(vertex_shader_id,
		GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertex_shader_id,
		GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		char* shader_error_message =
			(char*)malloc(info_log_length + 1);
		glGetShaderInfoLog(vertex_shader_id,
			info_log_length, 0, shader_error_message);
		printf(BRIGHTRED("compiling error %s\n"), shader_error_message);
	}

	printf("Compiling fragment shader\n");
	uint32 fragment_shader_id;
	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &source.fragment_shader, 0);
	glCompileShader(fragment_shader_id);

	glGetShaderiv(fragment_shader_id,
		GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragment_shader_id,
		GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		char* shader_error_message =
			(char*)malloc(info_log_length + 1);
		glGetShaderInfoLog(fragment_shader_id,
			info_log_length, 0, shader_error_message);
		printf(BRIGHTRED("compiling error %s\n"), shader_error_message);
		if (shader_error_message)
		{
			free(shader_error_message);
		}
	}

	printf("Linking program\n");
	uint32 shader_program_id = glCreateProgram();
	glAttachShader(shader_program_id, vertex_shader_id);
	glAttachShader(shader_program_id, fragment_shader_id);
	glLinkProgram(shader_program_id);

	glGetProgramiv(shader_program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(shader_program_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		char* shader_error_message =
			(char*)malloc(info_log_length + 1);
		glGetProgramInfoLog(shader_program_id,
			info_log_length, 0, shader_error_message);
		printf(BRIGHTRED("linking error %s\n"), shader_error_message);
		if (shader_error_message)
		{
			free(shader_error_message);
		}
	}

	glDetachShader(shader_program_id, vertex_shader_id);
	glDetachShader(shader_program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return shader_program_id;
}

void graphics_shader_delete(uint32_t renderId)
{
	glDeleteProgram(renderId);
}

void graphics_shader_bind(uint32_t renderId)
{
	glUseProgram(renderId);
}

void graphics_shader_unbind()
{
	glUseProgram(0);
}