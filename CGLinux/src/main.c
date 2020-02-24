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
#define HD 1
#define FULLHD 0

static i8 g_is_cursor_position_visible = 0;
static i8 g_is_cursor_enabled = 1;
static i8 g_is_freqency_visible = 0;
static u64 g_freqency;

#if HD == 1
f32 Width = 1280.0f; 
f32 Height = 720.0f;
#elif FULLHD == 1
f32 Width = 1920.0f; 
f32 Height = 1080.0f;
#else
f32 Width = 960; 
f32 Height = 640;
#endif

const char* shader_srcs = "CGLinux/resouce/simple_rotation_color_shader.glsl";
const char* shader_scs = "CGLinux/resouce/simple_color_shader.glsl";
const char* shader_ss = "CGLinux/resouce/simple_shader.glsl";

OrthographicCamera g_Camera;
RenderData g_RgbRenderData;
RenderData g_StaticRenderData;

f32 g_ZoomLevel = 1.0f;
f32 g_AspectRatio; //1.6f;

void window_mouse_scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset)
{
	if (yoffset < 0.0f || g_ZoomLevel > 0.2f)
	{
		g_ZoomLevel -= yoffset / 10;
	}
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

void window_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
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
	i32 isWindowCreated = window_create(&window, Width, Height, "Demo");
	if (isWindowCreated == -1) 
	{
		GLOG(RED("Can't create window!\n"));
	}
	
	window_set_scroll_callback(&window, window_mouse_scroll_callback);
	window_set_resize_callback(&window, window_resize_callback);

	//OpenGL
	i32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (status == 0)
	{
		GLOG(RED("Failed to init GLAD\n"));
	}
	GLOG(MAGNETA("OpenGL version %s\n"), glGetString(GL_VERSION));

	f32 asp = 1280.0f / 720.0f;
	GLOG("aspect ratio: %f\n", asp);

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
	
	g_Camera = orthographic_camera_create(
		-g_AspectRatio*g_ZoomLevel, g_AspectRatio*g_ZoomLevel, -g_ZoomLevel, g_ZoomLevel);

	GPosition position = (GPosition) { -0.5f, -0.5f, 0.01f, 0.01f };
	graphics_shader_source shader_source = {};
	shader_source = graphics_shader_load(shader_ss);
	u32 shader = graphics_shader_compile(shader_source);
	QuadArray quadArray = renderer_quad_array(shader, &g_Camera);
	char windowTitle[33];
	g_AspectRatio = Width / Height;

	while (!window_should_close(&window))
	{
		if (window_is_key_pressed(&window, KEY_ESCAPE))
		{
			window_set_should_close(&window, 1);
		}
		
		if (window_is_key_pressed(&window, KEY_A))
		{
			g_Camera.Position[0] -= 0.1;
		}
		else if (window_is_key_pressed(&window, KEY_D))
		{
			g_Camera.Position[0] += 0.1;
		}

		if (window_is_key_pressed(&window, KEY_W))
		{
			g_Camera.Position[1] += 0.1;
		}
		else if (window_is_key_pressed(&window, KEY_S))
		{
			g_Camera.Position[1] -= 0.1;
		}

		if (window_is_key_pressed(&window, KEY_Q))
		{
			g_Camera.Rotation += 0.1f;
		}
		else if (window_is_key_pressed(&window, KEY_E))
		{
			g_Camera.Rotation -= 0.1f;
		}

		sprintf (windowTitle, "Demo %f", g_ZoomLevel);
		window_set_title(window.GlfwWindow, windowTitle);
		orthographic_camera_set_projection(&g_Camera, 
			-g_AspectRatio*g_ZoomLevel, 
			g_AspectRatio*g_ZoomLevel, 
			-g_ZoomLevel, g_ZoomLevel);
		orthographic_camera_recalculate_view_matrix(&g_Camera);
	
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