#include "Sandbox.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

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

#include "Platform/Linux/Linux.h"

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

OrthographicCamera g_Camera;
f32 g_ZoomLevel = 1.0f;
f32 g_AspectRatio;

//Textures
const char* texture_anime_chibi = "CGLinux/resource/anime_chibi.png";
const char* texture_cherno_hazel_logo = "CGLinux/resource/Hazel.png";

void 
window_mouse_scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset)
{
	if (yoffset < 0.0f || g_ZoomLevel > 0.2f)
	{
		g_ZoomLevel -= yoffset / 10;
	}
}

void 
window_cursor_callback(GLFWwindow* window, f64 xpos, f64 ypos)
{
	//empty for now
}

void 
handle_dropped_file(const char* path)
{
	GLOG("Path of file = %s\n", path);
}

void 
window_drop_callback(GLFWwindow* window, i32 count, const char** paths)
{
	i32 i;
	for (i = 0; i < count; i++)
	{
		handle_dropped_file(paths[i]);
	}
}

void 
window_resize_callback(GLFWwindow* window, i32 width, i32 height)
{
    //Camera stuff
	g_AspectRatio = width / Width;
    //We can ResizeEvent.Invoke() here 
    //but we need EventSystmem for this
	orthographic_camera_set_projection(&g_Camera, 
		-g_AspectRatio * g_ZoomLevel, 
		 g_AspectRatio * g_ZoomLevel, 
		-g_ZoomLevel, g_ZoomLevel);
    //OpenGL stuff
	glViewport(0, 0, width, height);
}

void 
sandbox_start()
{
	//app
	//seting stack size
    linux_set_application_stack(MB(100), MB(128));

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

	g_Camera = orthographic_camera_create(
		-g_AspectRatio *g_ZoomLevel, 
		g_AspectRatio *g_ZoomLevel, 
		-g_ZoomLevel, g_ZoomLevel);
	char windowTitle[33];
	g_AspectRatio = Width / Height;
	GColor color = { 0.2f, 0.5f, 1.0f, 1.0f };

	mat4 transform_triangle;
	glm_mat4_identity(transform_triangle);
	Triangle triangle = 
		renderer_triangle_create((TriangleGeometry)
		{
			{ -0.9f, -0.9f }, 
			{ -0.1f, -0.9f },
			{ -0.5f,  0.7f }
		}, color, transform_triangle, &g_Camera);
	
	Rectangle rectangle = renderer_rectangle_create(
	  	(RectangleGeometry) { 0.5f, 0.5f, 1.5f, 1.0f }, color, &g_Camera);
	Rectangle rectangle2 = renderer_rectangle_create(
	  	(RectangleGeometry) { -1.5f, 0.5f, 1.5f, 0.5f }, color, &g_Camera);

	TexturedRectangle texturedRectangle = 
		renderer_create_textured_rectangle(
			(RectangleGeometry) { -0.5f, -0.5f, 1.0f, 1.0f }, 
			texture_cherno_hazel_logo,
			&g_Camera);
	TexturedRectangle texturedRectangle2 = 
		renderer_create_textured_rectangle(
			(RectangleGeometry) { -0.5f, -0.5f, 1.0f, 1.0f }, 
			texture_anime_chibi,
			&g_Camera);
	RectangleArray quadArray = 
		renderer_rectangle_array_create(&g_Camera);

    #if 0
	#endif
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
		
		GFORMAT(windowTitle, "Demo %f", g_ZoomLevel);
		window_set_title(window.GlfwWindow, windowTitle);

		orthographic_camera_set_projection(&g_Camera, 
			-g_AspectRatio*g_ZoomLevel, 
			g_AspectRatio*g_ZoomLevel, 
			-g_ZoomLevel, g_ZoomLevel);
		orthographic_camera_recalculate_view_matrix(&g_Camera);
	
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		#if 1
		renderer_triangle_draw(triangle);
		renderer_rectangle_draw(rectangle);
		renderer_rectangle_draw(rectangle2);
		renderer_rectangle_array_draw(quadArray);
		renderer_textured_rectangle_draw(texturedRectangle);
		renderer_textured_rectangle_draw(texturedRectangle2);
		#else
		#endif

		window_on_update(&window);
	}

	window_terminate();
	
	graphics_shader_delete_collection();
	renderer_triangle_destroy(triangle);
	
}
