#include "Shader.h"

#include <stdlib.h>
#include <stdio.h>
#include "Utils/IO.h"
#include "Utils/String.h"
#include "Utils/Array.h"
#include "Utils/Logger.h"

Shader* ShadersCollection = NULL;

ShaderSource
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
    ShaderSource source = {};

    shader_source = file_read_string(shader_path);
    shader_name = file_get_name_with_extension(shader_path);
    SHADERDEBUG(CYAN("shader source: %s\n"), shader_source);
    if (shader_source == NULL)
    {
        GERROR("shader file open error!");
	return (ShaderSource) { };
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

    SHADERDEBUG("vertex shader:\n"YELLOW("%s\n"), vertex_shader_source);
    SHADERDEBUG("fragment shader:\n"GREEN("%s\n"), fragment_shader_source);

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
    i32 is_compiled;
    GLCheck(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_compiled));
    if (is_compiled == GL_FALSE)
    {
        i32 log_length = 0;
        char error_message[1024];
        GLCheck(glGetShaderInfoLog(shader_id, 1024, &log_length, error_message));
        GERROR("shader_error_check[is_compiled: %d, log_length:%d]: %s\n", is_compiled, log_length, error_message);
    }
}

Shader
graphics_shader_compile(ShaderSource source)
{
    Shader shader = {};
    u32 vertex_shader_id;
    u32 fragment_shader_id;
    u32 shader_program_id;

    SHADERDEBUG(GREEN5("SHADER")" %s\n", source.name);

    if (source.vertex_shader == NULL ||
	source.fragment_shader == NULL ||
	vstring_length(source.vertex_shader) < 0 ||
	vstring_length(source.fragment_shader) < 0)
    {
	GERROR("Shader source is not loaded correctly!\n");
	return (Shader) {
	    .ShaderID = -1,
	    .UniformTable = NULL
	};
    }

    SHADERDEBUG(GREEN("Compiling")" vertex shader\n");
    GLCheck(vertex_shader_id = glCreateShader(GL_VERTEX_SHADER));
    GLCheck(glShaderSource(vertex_shader_id, 1, &source.vertex_shader, 0));
    GLCheck(glCompileShader(vertex_shader_id));
    shader_error_check(vertex_shader_id);

    SHADERDEBUG(GREEN("Compiling")" fragment shader\n");
    GLCheck(fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER));
    GLCheck(glShaderSource(fragment_shader_id, 1, &source.fragment_shader, 0));
    GLCheck(glCompileShader(fragment_shader_id));
    shader_error_check(fragment_shader_id);

    SHADERDEBUG(GREEN("Linking")" program\n");
    GLCheck(shader_program_id = glCreateProgram());
    SHADERDEBUG("SHADER ID: %d\n", shader_program_id);
    GLCheck(glAttachShader(shader_program_id, vertex_shader_id));
    GLCheck(glAttachShader(shader_program_id, fragment_shader_id));
    GLCheck(glLinkProgram(shader_program_id));
    shader_error_check(shader_program_id);

    GLCheck(glDetachShader(shader_program_id, vertex_shader_id));
    GLCheck(glDetachShader(shader_program_id, fragment_shader_id));

    GLCheck(glDeleteShader(vertex_shader_id));
    GLCheck(glDeleteShader(fragment_shader_id));

    shader.ShaderID = shader_program_id;
    shader.UniformTable = NULL;

    array_push(ShadersCollection, shader);

    return shader;
}

void
graphics_shader_delete(Shader* shader)
{
    GLCheck(glDeleteProgram(shader->ShaderID));
    shfree(shader->UniformTable);
}

void
graphics_shader_bind(Shader* shader)
{
    GLCheck(glUseProgram(shader->ShaderID));
}

void
graphics_shader_unbind()
{
    GLCheck(glUseProgram(0));
}

void
graphics_shader_delete_collection()
{
    Shader shader;
    for (i32 i = 0; i < array_len(ShadersCollection); i++)
    {
        shader = ShadersCollection[i];
        graphics_shader_delete(&shader);
    }

    GLOG(GREEN("Delete collection of shaders\n"));
}
