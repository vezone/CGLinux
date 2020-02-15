#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>

#include "vlib/core/vtypes.h"

#include "graphics/graphics_buffer.h"
#include "graphics/graphics_shader.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

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

typedef struct Triangle2D
{
	float a[2];
	float b[2];
	float c[2];
} Triangle2D;
#if 0
void
render_triangle(Triangle2D triangle2D)
{
	float vertices[3 * 3] =
	{
		triangle2D.a[0], triangle2D.a[1], 0.0f,
		triangle2D.b[0], triangle2D.b[1], 0.0f,
		triangle2D.c[0], triangle2D.c[1], 0.0f
	};
	graphics_vertex_buffer vb = {};
	graphics_vertex_buffer_create(&vb, vertices, sizeof(vertices));
	graphics_vertex_buffer_bind(&vb);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3 * sizeof(float), 0);
	
	uint32_t indices[] = { 0, 1, 2 };
	graphics_index_buffer ib = {};
	graphics_index_buffer_create(&ib, indices, 3);
	graphics_index_buffer_bind(&ib);
	graphics_shader_source shader_source;
	shader_source = graphics_shader_load("CGLinux/resouce/simple_shader.txt"); 
	uint32 shader = graphics_shader_compile(shader_source);
}
#endif

typedef struct RotationData {
	mat4 Matrix;
	vec3 Axis;
	float Angle;
} RotationData;

typedef struct RenderData {
	graphics_vertex_array VertexArray;
	uint32 Shader;
	RotationData Rotation;
} RenderData;

static void
render_data_print(RenderData renderData)
{
	printf("shader1: %d \n", renderData.Shader);
	printf("va1.id: %d \n", renderData.VertexArray.RendererID);
}

RenderData
render_data_create(const char* shader_path, float vertices[9])
{
	graphics_shader_source shader_source;
	shader_source = graphics_shader_load(shader_path); 
	uint32 shader = graphics_shader_compile(shader_source);
	graphics_shader_bind(shader);

	graphics_vertex_buffer vbo = {};
	graphics_vertex_buffer_create(&vbo, vertices, 36, data_type_float3);
	
	uint32 indices[] = { 0, 1, 2 };
	graphics_index_buffer ibo = {};
	graphics_index_buffer_create(&ibo, indices, ARRAY_LENGTH(indices));

	graphics_vertex_array va = {}; 
	graphics_vertex_array_create(&va);
	graphics_vertex_array_add_vbo(&va, vbo);
	graphics_vertex_array_add_ibo(&va, ibo);
	graphics_vertex_array_bind(&va);

	mat4 rotationMatrix = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	vec3 rotationAxis = { 0.0f, 0.0f, 1.0f };
	RotationData rotationData = {};
	glm_mat4_copy(rotationMatrix, rotationData.Matrix);
	glm_vec3_copy(rotationAxis, rotationData.Axis);
	rotationData.Angle = 0.1f;
	
	return ((RenderData) { va, shader, rotationData });
}

static void
render_data_render(RenderData renderData) 
{
	graphics_shader_bind(renderData.Shader);
	graphics_vertex_array_bind(&renderData.VertexArray);

	uint32 u_RotationMatrixLocation = glGetUniformLocation(renderData.Shader, "u_RotationMatrix");
	if (u_RotationMatrixLocation >= 0)
	{
		//glm_mat4_print(renderData.RotationData.RotationMatrix, stdout);
		glm_rotate(renderData.Rotation.Matrix, renderData.Rotation.Angle, renderData.Rotation.Axis);
		glUniformMatrix4fv(u_RotationMatrixLocation, 1, 0, renderData.Rotation.Matrix[0]);
		renderData.Rotation.Angle+= 0.01;
	}
	else 
	{
		printf(RED5("u_RotationMatrixLocation: %d\n"), u_RotationMatrixLocation);
	}

	glDrawElements(GL_TRIANGLES, renderData.VertexArray.IndexBuffer.Count, GL_UNSIGNED_INT, NULL);
}

int main()
{
	GLFWwindow* window;
	//GLFWWindow & OpenGL initialization stuff
	{
		if (!glfwInit())
		{
			printf("GLFW is not initialized!\n");
			return(-1);
		}
		int32 major, minor, revision;
		glfwGetVersion(&major, &minor, &revision);
		printf("GLFW version: %d.%d.%d\n", major, minor, revision);
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
			printf("Failed to init GLAD\n");
		}
		printf("OpenGL version %s\n", glGetString(GL_VERSION));
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

	float vertices22[3 * 3] =
	{
		 0.1f, 0.1f, 0.0f,
		 0.1f, 0.4f, 0.0f,
		-0.5f, 0.1f, 0.0f
	};

	float vertices3[3 * 3] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	RenderData rgbRenderData = render_data_create("CGLinux/resouce/simple_rotation_color_shader.glsl", vertices1);
	RenderData blueRenderData = render_data_create("CGLinux/resouce/simple_rotation_shader.glsl", vertices3);

	RenderData staticRenderData = render_data_create("CGLinux/resouce/simple_shader.glsl", vertices2);
	RenderData staticRenderData2 = render_data_create("CGLinux/resouce/simple_shader.glsl", vertices22);

	render_data_print(rgbRenderData);
	render_data_print(staticRenderData);
	render_data_print(blueRenderData);

	double mouse_x_pos, mouse_y_pos;
	while (!glfwWindowShouldClose(window))
	{
		g_freqency = glfwGetTimerFrequency();
		if (g_is_freqency_visible)
		{
			printf("%ld hz\n", g_freqency);
		}
		if (g_is_cursor_position_visible)
		{
			glfwGetCursorPos(window, &mouse_x_pos, &mouse_y_pos);
			printf("Mouse position: {%f,%f}\n", mouse_x_pos, mouse_y_pos);
		}

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render_data_render(staticRenderData);
		render_data_render(staticRenderData2);
		render_data_render(blueRenderData);
		render_data_render(rgbRenderData);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();

	return 0;
}
