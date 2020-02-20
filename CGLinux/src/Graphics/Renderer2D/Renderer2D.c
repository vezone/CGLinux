#include "Renderer2D.h"

#include <glad/glad.h>
#include "Utils/Logger.h"

void
render_data_print(RenderData renderData, const char* caller)
{
	printf(caller);
	printf("_shader: %d \n", renderData.Shader);
	printf(caller);
	printf("_va.id: %d \n", renderData.VertexArray.RendererID);
}

RenderData
render_data_create(const char* shader_path, f32 vertices[9], OrthographicCamera* camera)
{
	graphics_shader_source shader_source;
	u32 shader;
	VertexBuffer vbo = {};
	IndexBuffer ibo = {};
	VertexArray va = {};
	u32 indices[] = { 0, 1, 2 };
	vec3 rotationAxis = { 0.0f, 0.0f, 0.1f };
	RotationData rotationData = {};

	shader_source = graphics_shader_load(shader_path); 
	shader = graphics_shader_compile(shader_source);
	graphics_shader_bind(shader);

	graphics_vertex_buffer_create(&vbo, vertices, 36, Float3);
	graphics_index_buffer_create(&ibo, indices, ARRAY_LENGTH(indices));

	graphics_vertex_array_create(&va);
	graphics_vertex_array_add_vbo(&va, vbo);
	graphics_vertex_array_add_ibo(&va, ibo);
	graphics_vertex_array_bind(&va);

	glm_mat4_identity(rotationData.Matrix);
	glm_vec3_copy(rotationAxis, rotationData.Axis);
	rotationData.Angle = 0.01f;
	
	return ((RenderData) { shader, va, rotationData, camera });
}

void
render_data_render(RenderData* renderData) 
{
	u32 u_RotationMatrixLocation;
	u32 u_ColorLocation;
	static f32 r = 0.5f;
	static f32 incriment = 0.001f;
	
	orthographic_camera_recalculate_view_matrix(renderData->Camera);

	graphics_shader_bind(renderData->Shader);
	graphics_vertex_array_bind(&renderData->VertexArray);
	
	u_RotationMatrixLocation = glGetUniformLocation(renderData->Shader, "u_srcs_RotationMatrix");
	if (u_RotationMatrixLocation >= 0)
	{
		glm_rotate(renderData->Rotation.Matrix, 
			renderData->Rotation.Angle, 
			renderData->Rotation.Axis);
		glUniformMatrix4fv(u_RotationMatrixLocation, 1, 0, renderData->Rotation.Matrix[0]);
	}
	else
	{
		GLOG(RED("u_RotationMatrixLocation: %d\n"), u_RotationMatrixLocation);
	}

	u_RotationMatrixLocation = glGetUniformLocation(renderData->Shader, "u_ViewProjection");
	if (u_RotationMatrixLocation >= 0)
	{
		glUniformMatrix4fv(u_RotationMatrixLocation, 1, 0, renderData->Camera->ViewProjectionMatrix[0]);
	}
	else
	{
		GLOG(RED("u_RotationMatrixLocation: %d\n"), u_RotationMatrixLocation);
	}

	u_RotationMatrixLocation = glGetUniformLocation(renderData->Shader, "u_RotationMatrix");
	if (u_RotationMatrixLocation >= 0)
	{
		glm_rotate(renderData->Rotation.Matrix, 
			renderData->Rotation.Angle, 
			renderData->Rotation.Axis);
		glUniformMatrix4fv(u_RotationMatrixLocation, 1, 0, renderData->Rotation.Matrix[0]);
	}
	else
	{
		GLOG(RED("u_RotationMatrixLocation: %d\n"), u_RotationMatrixLocation);
	}

	u_ColorLocation = glGetUniformLocation(renderData->Shader, "u_Color");
	if (u_ColorLocation >= 0)
	{
		glUniform4f(u_ColorLocation, r, 0.3f, 0.8f, 1.0f);

		if (r >= 1.0f) {
			incriment = -0.001f;
		}
		else if (r <= 0.0f) {
			incriment = 0.001f;
		}
 
		r += incriment;
	}
	else 
	{
		GLOG(RED5("u_ColorLocation: %d\n"), u_ColorLocation);
	}

	glDrawElements(GL_TRIANGLES, renderData->VertexArray.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}
