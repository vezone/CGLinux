#include "Shader.h"
#include <stdlib.h>
#include <stdio.h>
#include "Utils/String.h"
#include "Utils/Array.h"
#include "Utils/Logger.h"

u32* ShadersCollection = NULL;

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

static char* 
file_read_string(const char* file_path)
{
	FILE* file;
	char* result;
	i32 file_length;

	file = fopen(file_path, "r");
	if (file)
	{	
		fseek(file, 0, SEEK_END);
		file_length = (ftell(file));
		fseek(file, 0, SEEK_SET);
		result = malloc((file_length + 1) * sizeof(char));
		
		fread(result, sizeof(char), (file_length), file);
		result[file_length] = '\0';
		
		fclose(file);
		return((char*)result);
	}
	
	return NULL;
}

graphics_shader_source 
graphics_shader_load(const char* shader_path)
{
	i32 vertex_index;
	i32 fragment_index;
	i32 vertex_keyword_length;
	i32 fragment_keyword_length;
	char* shader_source;
	char* shader_name;
	const char* vertex_shader_source;
	const char* fragment_shader_source;
	graphics_shader_source source = {};

	shader_source = file_read_string(shader_path);
	shader_name = file_get_name_with_extension(shader_path);
	SHADERDEBUG(CYAN("shader source: %s\n"), shader_source);
	if (shader_source == NULL)
	{
		SHADERLOG(BRIGHTRED("shader file open error!"));
	}
	   	
	vertex_index   = vstring_index_of_string(shader_source, "#vertex shader");
	fragment_index = vstring_index_of_string(shader_source, "#fragment shader");
	vertex_keyword_length = vstring_length("#vertex shader");
	fragment_keyword_length = vstring_length("#fragment shader");
	
	vertex_shader_source = vstring_substring_range(shader_source, 
			vertex_index + vertex_keyword_length + 1, 
			(fragment_index - 1));
	fragment_shader_source = 
		vstring_substring(shader_source, 
		fragment_index + fragment_keyword_length + 1);
	
	SHADERLOG("vertex shader:\n"YELLOW("%s\n"), vertex_shader_source);
    SHADERLOG("fragment shader:\n"GREEN("%s\n"), fragment_shader_source);
	
	source.name = shader_name;
	source.vertex_shader   = (const char*) vertex_shader_source;
	source.fragment_shader = (const char*) fragment_shader_source;

	if (shader_source)
	{
		free(shader_source);
	}

	return source;
}

static void
shader_error_check(u32 shader_id)
{
	i32 shader_compiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled == GL_FALSE)
	{
		i32 log_length = 0;
		char error_message[1024];
		glGetShaderInfoLog(shader_id, 1024, &log_length, error_message);
		SHADERLOG(BRIGHTRED("compiling error[is_compiled: %d, length:%d]: %s\n"), shader_compiled, log_length, error_message);
	}
}

u32 
graphics_shader_compile(graphics_shader_source source)
{
	SHADERDEBUG(GREEN5("SHADER")" %s\n", source.name);
	SHADERDEBUG(GREEN("Compiling")" vertex shader\n");
	u32 vertex_shader_id;

	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id, 1, &source.vertex_shader, 0);

	glCompileShader(vertex_shader_id);

	shader_error_check(vertex_shader_id);

	SHADERDEBUG(GREEN("Compiling")" fragment shader\n");
	u32 fragment_shader_id;
	//HERE WE GET AN ERROR
	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &source.fragment_shader, 0);
	glCompileShader(fragment_shader_id);
	shader_error_check(fragment_shader_id);

	SHADERDEBUG(GREEN("Linking")" program\n");
	u32 shader_program_id = glCreateProgram();
	SHADERDEBUG("SHADER ID: %d\n", shader_program_id);
	glAttachShader(shader_program_id, vertex_shader_id);
	glAttachShader(shader_program_id, fragment_shader_id);
	glLinkProgram(shader_program_id);
	shader_error_check(shader_program_id);

	glDetachShader(shader_program_id, vertex_shader_id);
	glDetachShader(shader_program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	array_push(ShadersCollection, shader_program_id);

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

void
graphics_shader_delete_collection()
{
	for (i32 i = 0; i < array_len(ShadersCollection); i++)
	{
		graphics_shader_delete(ShadersCollection[i]);
	}

	SHADERLOG(GREEN("Delete shader's collection\n"));
}
