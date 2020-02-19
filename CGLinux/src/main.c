#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>

#include "vlib/core/vtypes.h"

#include "graphics/graphics_buffer.h"
#include "graphics/graphics_shader.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))
#define TO_STRING(x) #x

#define ISGLOBALLOG 1
#define ISGLOBALDEBUG 1

#if ISGLOBALLOG == 1
	#define GLOG(...) printf(__VA_ARGS__)
#else
	#define GLOG(...)
#endif

#if ISGLOBALDEBUG == 1
	#define GDEBUG(...) printf(__VA_ARGS__)
#else
	#define GDEBUG(...)
#endif

// WINDOW GLOBAL
static int8 g_is_cursor_position_visible = 0;
static int8 g_is_cursor_enabled = 1;
static int8 g_is_freqency_visible = 0;
static uint64 g_freqency;

void window_key_callback(GLFWwindow* window, int32 key, int32 scancode, int32 action, int32 mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_Q:
			printf("Q is pressed\n");
			glfwSetWindowShouldClose(window, 1);
			break;
		case GLFW_KEY_W:
			printf("W is pressed\n");
			break;
		case GLFW_KEY_E:
			printf("E is pressed\n");
			break;
		case GLFW_KEY_R:
			printf("R is pressed\n");
			break;
		case GLFW_KEY_T:
			printf("T is pressed\n");
			break;
		case GLFW_KEY_Y:
			printf("Y is pressed\n");
			break;
		case GLFW_KEY_U:
			printf("U is pressed\n");
			break;
		case GLFW_KEY_I:
			printf("I is pressed\n");
			break;
		case GLFW_KEY_O:
			printf("O is pressed\n");
			break;
		case GLFW_KEY_P:
			printf("P is pressed\n");
			break;
		case GLFW_KEY_A:
			printf("A is pressed\n");
			break;
		case GLFW_KEY_S:
			if (!g_is_cursor_position_visible)
			{
				g_is_cursor_position_visible = 1;
			}
			else
			{
				g_is_cursor_position_visible = 0;
			}
			printf("S is pressed\n");
			break;
		case GLFW_KEY_D:
			if (!g_is_cursor_enabled)
			{
				g_is_cursor_enabled = 1;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else
			{
				g_is_cursor_enabled = 0;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			}
			printf("D is pressed\n");
			break;
		case GLFW_KEY_F:
			if (g_is_freqency_visible)
			{
				g_is_freqency_visible = 0;
			}
			else
			{
				g_is_freqency_visible = 1;
			}
			printf("F is pressed\n");
			break;
		case GLFW_KEY_G:
			printf("G is pressed\n");
			break;
		case GLFW_KEY_H:
			printf("H is pressed\n");
			break;
		case GLFW_KEY_J:
			printf("J is pressed\n");
			break;
		case GLFW_KEY_K:
			printf("K is pressed\n");
			break;
		case GLFW_KEY_L:
			printf("L is pressed\n");
			break;
		case GLFW_KEY_Z:
			printf("Z is pressed\n");
			break;
		case GLFW_KEY_X:
			printf("X is pressed\n");
			break;
		case GLFW_KEY_C:
			printf("C is pressed\n");
			break;
		case GLFW_KEY_V:
			printf("V is pressed\n");
			break;
		case GLFW_KEY_B:
			printf("B is pressed\n");
			break;
		case GLFW_KEY_N:
			printf("N is pressed\n");
			break;
		case GLFW_KEY_M:
			printf("M is pressed\n");
			break;
		case GLFW_KEY_0:
			printf("0 is pressed\n");
			break;
		case GLFW_KEY_1:
			printf("1 is pressed\n");
			break;
		case GLFW_KEY_2:
			printf("2 is pressed\n");
			break;
		case GLFW_KEY_3:
			printf("3 is pressed\n");
			break;
		case GLFW_KEY_4:
			printf("4 is pressed\n");
			break;
		case GLFW_KEY_5:
			printf("5 is pressed\n");
			break;
		case GLFW_KEY_6:
			printf("6 is pressed\n");
			break;
		case GLFW_KEY_7:
			printf("7 is pressed\n");
			break;
		case GLFW_KEY_8:
			printf("8 is pressed\n");
			break;
		case GLFW_KEY_9:
			printf("9 is pressed\n");
			break;
		case GLFW_KEY_LEFT_SHIFT:
			printf("LShift is pressed\n");
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			printf("RShift is pressed\n");
			break;
		case GLFW_KEY_UP:
			printf("Up is pressed\n");
			break;
		case GLFW_KEY_DOWN:
			printf("Down is pressed\n");
			break;
		case GLFW_KEY_LEFT:
			printf("Left is pressed\n");
			break;
		case GLFW_KEY_RIGHT:
			printf("Right is pressed\n");
			break;
		}
	}
}

void window_mouse_button_callback(GLFWwindow* window, int32 button, int32 action, int32 mods)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			printf("Left mouse button is pressed\n");
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			printf("Right mouse button is pressed\n");
		}
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			printf("Middle mouse button is pressed\n");
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			printf("Left mouse button is released\n");
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			printf("Right mouse button is released\n");
		}
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			printf("Middle mouse button is released\n");
		}
	}
}

void window_mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	printf("Scroll mouse {%f, %f}\n", xoffset, yoffset);
}

void window_cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	//empty for now
}

void handle_dropped_file(const char* path)
{
	printf("Path of file = %s\n", path);
}

void window_drop_callback(GLFWwindow* window, int32 count, const char** paths)
{
	int32 i;
	for (i = 0; i < count; i++)
	{
		handle_dropped_file(paths[i]);
	}
}

typedef struct OrthographicCamera {
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	mat4 ViewProjectionMatrix;
	vec3 Position;
	float Rotation; 
} OrthographicCamera;

typedef struct RotationData {
	mat4 Matrix;
	vec3 Axis;
	float Angle;
} RotationData;

typedef struct RenderData {
	VertexArray VertexArray;
	uint32 Shader;
	RotationData Rotation;
	OrthographicCamera Camera;
} RenderData;

#define RENDER_DATA_PRINT(renderData) render_data_print(renderData, #renderData)

static void
render_data_print(RenderData renderData, const char* caller)
{
	printf(caller);
	printf("_shader: %d \n", renderData.Shader);
	printf(caller);
	printf("_va.id: %d \n", renderData.VertexArray.RendererID);
}

OrthographicCamera 
orthographic_camera_create(float left, float right, float bot, float top)
{
	OrthographicCamera camera = {};
	glm_ortho(left, right, bot, top, -1.0f, 1.0f, camera.ProjectionMatrix);
	glm_mat4_identity(camera.ViewMatrix);
	glm_mat4_mul(camera.ProjectionMatrix, camera.ViewMatrix, camera.ViewProjectionMatrix);
	glm_vec3_zero(camera.Position);
	camera.Rotation = 0.0f;
}

void
orthographic_camera_set_projection(OrthographicCamera* camera, float left, float right, float bot, float top)
{
	glm_ortho(left, right, bot, top, -1.0f, 1.0f, camera->ProjectionMatrix);
	glm_mat4_mul(camera->ProjectionMatrix, camera->ViewMatrix, camera->ViewProjectionMatrix);
}

void
orthographic_camera_recalculate_view_matrix(OrthographicCamera* camera)
{
	mat4 identityTranslate = GLM_MAT4_IDENTITY_INIT;
	mat4 identityRotate = GLM_MAT4_IDENTITY_INIT;
	mat4 transform = {};
	vec3 rotate_vec = { 0.0f, 0.0f, 1.0f };
	glm_translate(identityTranslate, camera->Position);
	glm_rotate(identityRotate, glm_rad(camera->Rotation), rotate_vec);
	glm_mat4_mul(identityTranslate, identityRotate, transform);
	glm_mat4_inv(transform, camera->ViewMatrix);
	glm_mat4_mul(camera->ProjectionMatrix, camera->ViewMatrix, camera->ViewProjectionMatrix);
}

RenderData
render_data_create(const char* shader_path, float vertices[9], OrthographicCamera camera)
{
	graphics_shader_source shader_source;
	shader_source = graphics_shader_load(shader_path); 
	uint32 shader = graphics_shader_compile(shader_source);
	graphics_shader_bind(shader);

	VertexBuffer vbo = {};
	graphics_vertex_buffer_create(&vbo, vertices, 36, Float3);
	
	uint32 indices[] = { 0, 1, 2 };
	IndexBuffer ibo = {};
	graphics_index_buffer_create(&ibo, indices, ARRAY_LENGTH(indices));

	VertexArray va = {}; 
	graphics_vertex_array_create(&va);
	graphics_vertex_array_add_vbo(&va, vbo);
	graphics_vertex_array_add_ibo(&va, ibo);
	graphics_vertex_array_bind(&va);

	mat4 rotationMatrix = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	vec3 rotationAxis = { 0.0f, 0.0f, 0.1f };
	RotationData rotationData = {};
	glm_mat4_copy(rotationMatrix, rotationData.Matrix);
	glm_vec3_copy(rotationAxis, rotationData.Axis);
	rotationData.Angle = 0.01f;
	
	return ((RenderData) { va, shader, rotationData });
}

static void
render_data_render(RenderData* renderData) 
{
	graphics_shader_bind(renderData->Shader);
	graphics_vertex_array_bind(&renderData->VertexArray);
	
	uint32 u_RotationMatrixLocation = glGetUniformLocation(renderData->Shader, "u_srcs_RotationMatrix");
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
		glUniformMatrix4fv(u_RotationMatrixLocation, 1, 0, renderData->Camera.ViewProjectionMatrix[0]);
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

	uint32 u_ColorLocation = glGetUniformLocation(renderData->Shader, "u_Color");
	static float r = 0.5f;
	static float incriment = 0.001f;
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

int main()
{
	GLFWwindow* window;
	//GLFWWindow & OpenGL initialization stuff
	{
		if (!glfwInit())
		{
			GLOG(RED("GLFW is not initialized!\n"));
			return(-1);
		}
		int32 major, minor, revision;
		glfwGetVersion(&major, &minor, &revision);
		GLOG(MAGNETA("GLFW version: %d.%d.%d\n"), major, minor, revision);
		window = glfwCreateWindow(1280, 720, "Demo", 0, 0);
		if (!window)
		{
			glfwTerminate();
			return(-1);
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		glfwSetKeyCallback(window, window_key_callback);
		glfwSetMouseButtonCallback(window, window_mouse_button_callback);
		glfwSetScrollCallback(window, window_mouse_scroll_callback);
		glfwSetDropCallback(window, window_drop_callback);
		
		//OpenGL
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 0)
		{
			GLOG(RED("Failed to init GLAD\n"));
		}
		GLOG(MAGNETA("OpenGL version %s\n"), glGetString(GL_VERSION));
	}

	float vertices1[3 * 3] =
	{
		-0.9f, -0.9f, 0.0f,
		 -0.1f, -0.9f, 0.0f,
		 0.0f,  0.3f, 0.0f
	};
	
	float vertices2[3 * 3] =
	{
		 0.9f, 0.9f, 0.0f,
		 0.9f, 0.7f, 0.0f,
		-0.5f, 0.7f, 0.0f
	};

	float vertices3[3 * 3] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	OrthographicCamera camera;
	camera = orthographic_camera_create(-1.0f, 1.0f, -1.0f, 1.0f);
	
	RenderData rgbRenderData = render_data_create("CGLinux/resouce/simple_rotation_color_shader.glsl", vertices1, camera);
	RenderData staticRenderData = render_data_create("CGLinux/resouce/simple_shader.glsl", vertices2, camera);

	//RENDER_DATA_PRINT(rgbRenderData);
	//RENDER_DATA_PRINT(staticRenderData);

	double mouse_x_pos, mouse_y_pos;
	while (!glfwWindowShouldClose(window))
	{
		g_freqency = glfwGetTimerFrequency();
		if (g_is_freqency_visible)
		{
			GLOG("%ld hz\n", g_freqency);
		}
		if (g_is_cursor_position_visible)
		{
			glfwGetCursorPos(window, &mouse_x_pos, &mouse_y_pos);
			GLOG("Mouse position: {%f,%f}\n", mouse_x_pos, mouse_y_pos);
		}

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		render_data_render(&staticRenderData);
	    render_data_render(&rgbRenderData);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();

	graphics_shader_delete(rgbRenderData.Shader);
	graphics_shader_delete(staticRenderData.Shader);

	return 0;
}
