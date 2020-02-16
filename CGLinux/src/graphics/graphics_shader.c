#include "graphics_shader.h"
#include "../vlib/core/vstring.h"

#include <glad/glad.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void 
file_write_string(char* file_path, char* data, int32 len)
{
	FILE* file;
	file = fopen(file_path, "w");
	fwrite(data, 1, len, file);
	fclose(file);
}

static const char* 
file_read_string(const char* file_path)
{
	FILE* file;
	file = fopen(file_path, "r");
	if (file)
	{
		char* result;
		long file_length;

		fseek(file, 0, SEEK_END);
		file_length = (ftell(file));
		fseek(file, 0, SEEK_SET);
		result = malloc((file_length + 1) * sizeof(char));
		memset(result, '\0', (file_length + 1));
		fread(result, sizeof(char), (file_length), file);
		
		fclose(file);
		return((const char*)result);
	}
	return("file_open_error");
}

graphics_shader_source 
graphics_shader_load(const char* shader_path)
{
	const char* shader_source = file_read_string(shader_path);
	SHADERDEBUG(CYAN("shader source: %s\n"), shader_source);
	if (vstring_compare(shader_source, "file_open_error"))
	{
		asserts(0, BRIGHTRED("shader file open error!"));
	}
	int32 vertex_index   = vstring_index_of_string(shader_source, "#vertex shader");
	int32 fragment_index = vstring_index_of_string(shader_source, "#fragment shader");
	int32 vertex_keyword_length = vstring_length("#vertex shader");
	int32 fragment_keyword_length = vstring_length("#fragment shader");

	assert(vertex_index >=  0);
	assert(fragment_index > vertex_index);

	const char* vertex_shader_source = 
		vstring_substring_range(shader_source, 
			vertex_index + vertex_keyword_length, 
			(fragment_index - 1));
	const char* fragment_shader_source = 
		vstring_substring(shader_source, 
		fragment_index + vstring_length("#fragment shader")+1);
	
	SHADERDEBUG(YELLOW("vertex shader:\n%s\n"), vertex_shader_source);
	SHADERDEBUG(GREEN("shader shader:\n%s\n"), fragment_shader_source);
	
	assert(vstring_length(vertex_shader_source) > 0);
	assert(vstring_length(fragment_shader_source) > 0);
	
	return (graphics_shader_source) 
	{ 
		(const char*) vertex_shader_source, 
		(const char*) fragment_shader_source 
	};
}

uint32 
graphics_shader_compile(graphics_shader_source source)
{
	uint32 vertex_shader_id;
	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

	SHADERLOG(GREEN("Compiling")" vertex shader\n");
	glShaderSource(vertex_shader_id, 1, &source.vertex_shader, 0);
	glCompileShader(vertex_shader_id);

	int32 result = GL_FALSE;
	int32 info_log_length;
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		char* shader_error_message = malloc(info_log_length + 1);
		glGetShaderInfoLog(vertex_shader_id, info_log_length, 0, shader_error_message);
		SHADERLOG(BRIGHTRED("compiling error %s\n"), shader_error_message);
		free(shader_error_message);
	}

	SHADERLOG(GREEN("Compiling")" fragment shader\n");
	uint32 fragment_shader_id;
	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &source.fragment_shader, 0);
	glCompileShader(fragment_shader_id);

	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		char* shader_error_message = malloc(info_log_length + 1);
		glGetShaderInfoLog(fragment_shader_id, info_log_length, 0, shader_error_message);
		SHADERLOG(BRIGHTRED("compiling error %s\n"), shader_error_message);
		free(shader_error_message);
	}

	SHADERLOG(GREEN("Linking")" program\n");
	uint32 shader_program_id = glCreateProgram();
	glAttachShader(shader_program_id, vertex_shader_id);
	glAttachShader(shader_program_id, fragment_shader_id);
	glLinkProgram(shader_program_id);

	glGetProgramiv(shader_program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(shader_program_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		char* shader_error_message = malloc(info_log_length + 1);
		glGetProgramInfoLog(shader_program_id, info_log_length, 0, shader_error_message);
		SHADERLOG(BRIGHTRED("linking error %s\n"), shader_error_message);
		free(shader_error_message);
	}

	glDetachShader(shader_program_id, vertex_shader_id);
	glDetachShader(shader_program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return shader_program_id;
}

void 
graphics_shader_delete(uint32 renderId)
{
	glDeleteProgram(renderId);
}

void 
graphics_shader_bind(uint32 renderId)
{
	glUseProgram(renderId);
}

void 
graphics_shader_unbind()
{
	glUseProgram(0);
}