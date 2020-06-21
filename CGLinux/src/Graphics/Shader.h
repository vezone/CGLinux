#pragma once

#include <glad/glad.h>
#include "OpenGLBase.h"
#include "Utils/Types.h"
#include "Utils/Logger.h"
#include "Utils/stb_ds.h"

typedef struct ShaderSource
{
	char* name;
	const char* vertex_shader;
	const char* fragment_shader;
} ShaderSource;

typedef struct UniformTableType { 
	const char* key;
	i32 value;
} UniformTableType;
	
typedef struct Shader
{
	u32 ShaderID;
	UniformTableType* UniformTable;
} Shader;

ShaderSource
graphics_shader_load(const char* shader_path);

Shader 
graphics_shader_compile(ShaderSource source);

void 
graphics_shader_delete(Shader* shader);

void 
graphics_shader_bind(Shader* shader);

void 
graphics_shader_unbind();

void
graphics_shader_delete_collection();

static void
graphics_shader_set_1float(Shader* shader, const char* uniformName, f32 v0)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	  GLCheck(glUniform1f(location, v0));
	}
}

static void
graphics_shader_set_2float(Shader* shader, const char* uniformName, f32 v0, f32 v1)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	  GLCheck(glUniform2f(location, v0, v1));
	}
}

static void
graphics_shader_set_3float(Shader* shader, const char* uniformName, f32 v0, f32 v1, f32 v2)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	  GLCheck(glUniform3f(location, v0, v1, v2));	
    }
}

static void
graphics_shader_set_4float(Shader* shader, const char* uniformName, f32 v0, f32 v1, f32 v2, f32 v3)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	  GLCheck(glUniform4f(location, v0, v1, v2, v3));
	}
}


static void
graphics_shader_set_1int(Shader* shader, const char* uniformName, i32 v0)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform1i(location, v0));
	}
}

static void
graphics_shader_set_2int(Shader* shader, const char* uniformName, i32 v0, i32 v1)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform2i(location, v0, v1));
	}
}

static void
graphics_shader_set_3int(Shader* shader, const char* uniformName, i32 v0, i32 v1, i32 v2)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform3i(location, v0, v1, v2));
	}
}

static void
graphics_shader_set_4int(Shader* shader, const char* uniformName, i32 v0, i32 v1, i32 v2, i32 v3)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform4i(location, v0, v1, v2, v3));
	}
}

static void
graphics_shader_set_1uint(Shader* shader, const char* uniformName, u32 v0)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform1ui(location, v0));
	}
}

static void
graphics_shader_set_2uint(Shader* shader, const char* uniformName, u32 v0, u32 v1)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform2ui(location, v0, v1));
	}
}

static void
graphics_shader_set_3uint(Shader* shader, const char* uniformName, u32 v0, u32 v1, u32 v2)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform3ui(location, v0, v1, v2));
	}
}

static void
graphics_shader_set_4uint(Shader* shader, const char* uniformName, u32 v0, u32 v1, u32 v2, u32 v3)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform4ui(location, v0, v1, v2, v3));
	}
}


static void
graphics_shader_set_float1(Shader* shader, const char* uniformName, i32 count, f32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}
	
	if (location >= 0)
	{
	    GLCheck(glUniform1fv(location, count, values));
	}
}

static void
graphics_shader_set_float2(Shader* shader, const char* uniformName, i32 count, f32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform2fv(location, count, values));
	}
}

static void
graphics_shader_set_float3(Shader* shader, const char* uniformName, i32 count, f32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform3fv(location, count,  values));
	}
}

static void
graphics_shader_set_float4(Shader* shader, const char* uniformName, i32 count, f32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform4fv(location, count, values));
	}
}

static void
graphics_shader_set_int1(Shader* shader, const char* uniformName, i32 count, i32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform1iv(location, count, values));
	}
}

static void
graphics_shader_set_int2(Shader* shader, const char* uniformName, i32 count, i32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform2iv(location, count, values));
	}
}

static void
graphics_shader_set_int3(Shader* shader, const char* uniformName, i32 count, i32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform3iv(location, count, values));
	}
}

static void
graphics_shader_set_int4(Shader* shader, const char* uniformName, i32 count, i32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform4iv(location, count, values));
	}
}

static void
graphics_shader_set_uint1(Shader* shader, const char* uniformName, i32 count, u32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform4uiv(location, count, values));
	}
}

static void
graphics_shader_set_uint2(Shader* shader, const char* uniformName, i32 count, u32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform2uiv(location, count, values));
	}
}

static void
graphics_shader_set_uint3(Shader* shader, const char* uniformName, i32 count, u32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform3uiv(location, count, values));
	}
}

static void
graphics_shader_set_uint4(Shader* shader, const char* uniformName, i32 count, u32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniform4uiv(location, count, values));
	}
}

static void
graphics_shader_set_mat2(Shader* shader, const char* uniformName, i32 count, i8 transpose, f32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniformMatrix2fv(location, count, transpose, values));
	}
}

static void
graphics_shader_set_mat3(Shader* shader, const char* uniformName, i32 count, i8 transpose, f32* values)
{
	i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniformMatrix3fv(location, count, transpose, values));
	}
}

static void
graphics_shader_set_mat4(Shader* shader, const char* uniformName, i32 count, i8 transpose, f32* values)
{
    i32 location = shgeti(shader->UniformTable, uniformName);
	if (location == -1)
	{
	    GLCheck(location = glGetUniformLocation(shader->ShaderID, uniformName));
		shput(shader->UniformTable, uniformName, location);
	}
	else
	{
		location = shget(shader->UniformTable, uniformName);
	}

	if (location >= 0)
	{
	    GLCheck(glUniformMatrix4fv(location, count, transpose, values));
	}
}
