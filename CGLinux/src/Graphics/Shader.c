#include "Shader.h"
#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include "Utils/String.h"

static char*
file_get_name_with_extension(const char* path)
{
	i32 i, last_index = 0, name_index, new_length;
	i32 path_length = vstring_length(path);
	char* file_name;

	for (i = 0; i < path_length; i++)
	{
		if (path[i] == '/')
		{
			last_index = i;
		}
	}

	if (last_index != 0)
	{
		name_index = (last_index + 1);
	}
	else 
	{
		name_index = 0;
	}

	new_length = path_length - name_index;
	file_name = malloc((new_length + 1) * sizeof(char));
	for (i = name_index; i < path_length; i++)
	{
		file_name[i - name_index] = path[i];
	}
	file_name[new_length] = '\0';
	return file_name;
}

static void 
file_write_string(char* file_path, char* data, i32 len)
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
		i32 file_length;

		fseek(file, 0, SEEK_END);
		file_length = (ftell(file));
		fseek(file, 0, SEEK_SET);
		result = malloc((file_length + 1) * sizeof(char));
		vstring_set(result, '\0', (file_length + 1));
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
	char* shader_name = file_get_name_with_extension(shader_path);
	SHADERDEBUG(CYAN("shader source: %s\n"), shader_source);
	if (vstring_compare(shader_source, "file_open_error"))
	{
		printf(BRIGHTRED("shader file open error!"));
	}
	
	int32 vertex_index   = vstring_index_of_string(shader_source, "#vertex shader");
	int32 fragment_index = vstring_index_of_string(shader_source, "#fragment shader");
	int32 vertex_keyword_length = vstring_length("#vertex shader");
	int32 fragment_keyword_length = vstring_length("#fragment shader");

	const char* vertex_shader_source = 
		vstring_substring_range(shader_source, 
			vertex_index + vertex_keyword_length, 
			(fragment_index - 1));
	const char* fragment_shader_source = 
		vstring_substring(shader_source, 
		fragment_index + vstring_length("#fragment shader")+1);
	
	SHADERDEBUG(YELLOW("vertex shader:\n%s\n"), vertex_shader_source);
	SHADERDEBUG(GREEN("shader shader:\n%s\n"), fragment_shader_source);
	
	graphics_shader_source source = {};
	source.name = shader_name;
	source.vertex_shader = (const char*) vertex_shader_source;
	source.fragment_shader = (const char*) fragment_shader_source;
	
	return source;
}

static void
shader_error_check(u32 shader_id)
{
	i32 shader_compiled = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled < 0)
	{
		printf("Shader compiled: %d\n", shader_compiled);
		i32 log_length = 0;
		char error_message[1024];
		glGetShaderInfoLog(shader_id, 1024, &log_length, error_message);
		SHADERLOG(BRIGHTRED("compiling error %s\n"), error_message);
	}
}

u32 
graphics_shader_compile(graphics_shader_source source)
{
	SHADERLOG(GREEN5("SHADER")" %s\n", source.name);
	SHADERLOG(GREEN("Compiling")" vertex shader\n");
	u32 vertex_shader_id;
	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id, 1, &source.vertex_shader, 0);
	glCompileShader(vertex_shader_id);
	shader_error_check(vertex_shader_id);

	SHADERLOG(GREEN("Compiling")" fragment shader\n");
	u32 fragment_shader_id;
	//HERE WE GET AN ERROR
	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &source.fragment_shader, 0);
	glCompileShader(fragment_shader_id);
	shader_error_check(fragment_shader_id);

	SHADERLOG(GREEN("Linking")" program\n");
	u32 shader_program_id = glCreateProgram();
	SHADERLOG("SHADER ID: %d\n", shader_program_id);
	glAttachShader(shader_program_id, vertex_shader_id);
	glAttachShader(shader_program_id, fragment_shader_id);
	glLinkProgram(shader_program_id);
	shader_error_check(shader_program_id);

	glDetachShader(shader_program_id, vertex_shader_id);
	glDetachShader(shader_program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
	return shader_program_id;
}

void 
graphics_shader_delete(u32 renderId)
{
	glDeleteProgram(renderId);
}

void 
graphics_shader_bind(u32 renderId)
{
	glUseProgram(renderId);
}

void 
graphics_shader_unbind()
{
	glUseProgram(0);
}