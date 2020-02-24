#include <sys/resource.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>

#include "Utils/Types.h"
#include "Utils/String.h"
#include "Utils/Logger.h"
#include "Utils/Array.h"

#include "Graphics/Window.h"
#include "Graphics/KeyCodes.h"
#include "Graphics/Buffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Renderer2D/Renderer2D.h"
#include "Graphics/Renderer2D/OrthographicCamera.h"

#include "Graphics/Feature2D/Tilemap.h"

// WINDOW GLOBAL
static i8 g_is_cursor_position_visible = 0;
static i8 g_is_cursor_enabled = 1;
static i8 g_is_freqency_visible = 0;
static u64 g_freqency;

const char* shader_srcs = "CGLinux/resouce/simple_rotation_color_shader.glsl";
const char* shader_scs = "CGLinux/resouce/simple_color_shader.glsl";
const char* shader_ss = "CGLinux/resouce/simple_shader.glsl";

OrthographicCamera g_Camera;
RenderData g_RgbRenderData;
RenderData g_StaticRenderData;

#define HD 1
#define FULLHD 0

void window_key_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_Q:
			printf("Q is pressed\n");
			glfwSetWindowShouldClose(window, 1);
			break;
		case GLFW_KEY_W:
			printf("W is pressed\n");
			g_Camera.Position[1] += 0.1;
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
			g_Camera.Position[0] -= 0.1;
			break;
		case GLFW_KEY_S:
			g_Camera.Position[1] -= 0.1;
			// if (!g_is_cursor_position_visible)
			// {
			// 	g_is_cursor_position_visible = 1;
			// }
			// else
			// {
			// 	g_is_cursor_position_visible = 0;
			// }
			printf("S is pressed\n");
			break;
		case GLFW_KEY_D:
			g_Camera.Position[0] += 0.1;
			// if (!g_is_cursor_enabled)
			// {
			// 	g_is_cursor_enabled = 1;
			// 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// }
			// else
			// {
			// 	g_is_cursor_enabled = 0;
			// 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			// }
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
		}
	}
}

void window_mouse_button_callback(GLFWwindow* window, i32 button, i32 action, i32 mods)
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

void window_mouse_scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset)
{
	printf("Scroll mouse {%f, %f}\n", xoffset, yoffset);
}

void window_cursor_callback(GLFWwindow* window, f64 xpos, f64 ypos)
{
	//empty for now
}

void handle_dropped_file(const char* path)
{
	printf("Path of file = %s\n", path);
}

void window_drop_callback(GLFWwindow* window, i32 count, const char** paths)
{
	i32 i;
	for (i = 0; i < count; i++)
	{
		handle_dropped_file(paths[i]);
	}
}

int main()
{
	//app
	//seting stack size
	{
		struct rlimit resource_limit;
		int result = getrlimit(RLIMIT_STACK, &resource_limit);
		if (result < 0)
		{
			GLOG(RED("get r limit error!\n"));
		}
		else 
		{
			GLOG("Resource limit: %lld\n", (i64)resource_limit.rlim_cur, (i64)resource_limit.rlim_max);
			resource_limit.rlim_cur = (i64) MB(100);
			resource_limit.rlim_max = (i64) MB(128);
			result = setrlimit(RLIMIT_STACK, &resource_limit);
			if (result == 0) 
			{
				GLOG(YELLOW("NEW") "Resource limit: %lld mb\n", 
				(i64)TOMB(resource_limit.rlim_cur), (i64)resource_limit.rlim_max);
			}
		}
	}

	Window window = {};
	i32 isWindowCreated = window_create(&window, 
	#if HD == 1
		1280, 720,
	#elif FULLHD == 1
		1920, 1080,
	#else
		960, 640,
	#endif
		"Demo");
	if (isWindowCreated == -1) 
	{
		GLOG(RED("Can't create window!\n"));
	}
	
	//OpenGL
	i32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (status == 0)
	{
		GLOG(RED("Failed to init GLAD\n"));
	}
	GLOG(MAGNETA("OpenGL version %s\n"), glGetString(GL_VERSION));

	f32 vertices1[3 * 3] =
	{
		-0.9f, -0.9f, 0.0f,
		 -0.1f, -0.9f, 0.0f,
		 0.0f,  0.3f, 0.0f
	};
	
	f32 vertices2[3 * 3] =
	{
		 0.9f, 0.9f, 0.0f,
		 0.9f, 0.7f, 0.0f,
		-0.5f, 0.7f, 0.0f
	};

	g_RgbRenderData = render_data_create(shader_srcs, vertices1, &g_Camera);
	g_StaticRenderData = render_data_create(shader_scs, vertices2, &g_Camera);

	g_Camera = orthographic_camera_create(-1.6f, 1.6f, -0.9f, 0.9f);

	GPosition position = (GPosition) { -0.5f, -0.5f, 0.01f, 0.01f };
	graphics_shader_source shader_source = {};
	shader_source = graphics_shader_load(shader_ss);
	u32 shader = graphics_shader_compile(shader_source);
	QuadArray quadArray = renderer_quad_array(shader, &g_Camera);

	while (!window_should_close(&window))
	{
		if (window_is_key_pressed(&window, KEY_Q))
		{
			window_set_should_close(&window, 1);
		}
		
		if (window_is_key_pressed(&window, KEY_A))
		{
			g_Camera.Position[0] -= 0.1;
		}

		if (window_is_key_pressed(&window, KEY_D))
		{
			g_Camera.Position[0] += 0.1;
		}

		if (window_is_key_pressed(&window, KEY_W))
		{
			g_Camera.Position[1] += 0.1;
		}

		if (window_is_key_pressed(&window, KEY_S))
		{
			g_Camera.Position[1] -= 0.1;
		}

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		renderer_quad_array_draw(quadArray);

		render_data_render(&g_StaticRenderData);
	    render_data_render(&g_RgbRenderData);

		window_on_update(&window);
	}

	window_terminate();
	
	graphics_shader_delete(g_RgbRenderData.Shader);
	graphics_shader_delete(g_StaticRenderData.Shader);

	return 0;
}