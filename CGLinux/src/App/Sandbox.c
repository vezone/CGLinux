#include "Sandbox.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

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
#define DRAW_BASE_SCENE 1

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

static i8 g_is_cursor_position_visible = 0;
static i8 g_is_cursor_enabled = 1;
static i8 g_is_freqency_visible = 0;
static u64 g_freqency;

f32 g_CameraSpeed = 4.0f;
OrthographicCamera g_Camera;
f32 g_ZoomLevel = 1.0f;
f32 g_AspectRatio;

f32 g_TimeStep = 0.0f;
f32 g_LastFrameTime = 0.0f;

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

i32 
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
		return(-1);
	}
	
	window_set_vsync(1);
	window_set_scroll_callback(&window, window_mouse_scroll_callback);
	window_set_resize_callback(&window, window_resize_callback);

	//OpenGL
	i32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (status == 0)
	{
		GLOG(RED("Failed to init GLAD\n"));
		return(-1);
	}
	GLOG(MAGNETA("OpenGL version %s\n"), glGetString(GL_VERSION));

	g_Camera = orthographic_camera_create(
		-g_AspectRatio *g_ZoomLevel, 
		g_AspectRatio *g_ZoomLevel, 
		-g_ZoomLevel, g_ZoomLevel);
	g_AspectRatio = Width / Height;

	char windowTitle[33];
	vec4 triangleColor = { 0.2f, 0.5f, 1.0f, 1.0f };
	vec4 redColor = { 0.8f, 0.1f, 0.1f, 1.0f };
	vec4 yellowColor = { 1.0f, 1.0f, 0.0f, 1.0f };
	vec4 blueColor = { 0.1f, 0.1f, 0.8f, 1.0f };

	Shader texturedShader = graphics_shader_compile(		graphics_shader_load("CGLinux/resource/simple_texture_shader.glsl"));
	Shader positionGradientShader = graphics_shader_compile(		graphics_shader_load("CGLinux/resource/simple_shader.glsl"));
	Shader colorShader = graphics_shader_compile(		graphics_shader_load("CGLinux/resource/simple_color_shader.glsl"));
	Shader batchedColorShader = graphics_shader_compile(		graphics_shader_load("CGLinux/resource/simple_batched_color_shader.glsl"));
	
	Texture2D hazelLogoTexture = graphics_texture2d_create("CGLinux/resource/Hazel.png");
	Texture2D chibiTexture = graphics_texture2d_create("CGLinux/resource/AnimeChibi.png");

	BaseObject chibiRectangle = renderer_create_textured_rectangle(-0.5f, -0.5f);
	BaseObject hazelRectangle = renderer_create_textured_rectangle(-0.5f, -0.5f);
	
	color_renderer_batch_init();	

    i32 movementControlState = 1;
	f32 tempTime;
	while (!window_should_close(&window))
	{
		tempTime = (f32) glfwGetTime();
		g_TimeStep = tempTime - g_LastFrameTime;
		g_LastFrameTime = tempTime;

		if (window_is_key_pressed(&window, KEY_ESCAPE))
		{
			window_set_should_close(&window, 1);
		}

		if (window_is_key_pressed(&window, KEY_SPACE))
		{
			if (movementControlState == 1)
			{
				movementControlState = 2;
				GLOG("movementControlState switched to chibi!\n");
			}
			else
			{
				movementControlState = 1;
				GLOG("movementControlState switched to camera!\n");
			}
		}

		if (movementControlState == 1)
		{
			if (window_is_key_pressed(&window, KEY_W))
			{
				g_Camera.Position[1] += g_CameraSpeed * g_TimeStep;
			}
			else if (window_is_key_pressed(&window, KEY_S))
	    	{
	    		g_Camera.Position[1] -= g_CameraSpeed * g_TimeStep;
	    	}
			
			if (window_is_key_pressed(&window, KEY_A))
			{
				g_Camera.Position[0] -= g_CameraSpeed * g_TimeStep;
			}
			else if (window_is_key_pressed(&window, KEY_D))
			{
				g_Camera.Position[0] += g_CameraSpeed * g_TimeStep;
			}
		}
#if DRAW_BASE_SCENE == 1
		else
		{		
			if (window_is_key_pressed(&window, KEY_W))
			{
				chibiRectangle.Geometry.Position[1] += 0.5f * g_TimeStep;
			}
			else if (window_is_key_pressed(&window, KEY_S))
	    	{
				chibiRectangle.Geometry.Position[1] -= 0.5f * g_TimeStep;
	    	}
			
			if (window_is_key_pressed(&window, KEY_A))
			{
				chibiRectangle.Geometry.Position[0] -= 0.5f * g_TimeStep;
			}
			else if (window_is_key_pressed(&window, KEY_D))
			{
				chibiRectangle.Geometry.Position[0] += 0.5f * g_TimeStep;
			}	
		}
#endif	
		
		if (window_is_key_pressed(&window, KEY_Q))
		{
			g_Camera.Rotation += 0.1f * g_TimeStep;
		}
		else if (window_is_key_pressed(&window, KEY_E))
		{
			g_Camera.Rotation -= 0.1f * g_TimeStep;
		}
		
		GFORMAT(windowTitle, "Demo %f %f ms", g_ZoomLevel, 1000*g_TimeStep);
		window_set_title(window.GlfwWindow, windowTitle);

		orthographic_camera_set_projection(&g_Camera, 
			-g_AspectRatio*g_ZoomLevel, 
			g_AspectRatio*g_ZoomLevel, 
			-g_ZoomLevel, g_ZoomLevel);
		orthographic_camera_recalculate_view_matrix(&g_Camera);
	
		glClearColor(0.2f, 0.345f, 0.456f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
#if DRAW_BASE_SCENE == 1

		renderer_draw_textured_rectangle(&hazelRectangle, &texturedShader, &hazelLogoTexture, &g_Camera);
		renderer_draw_textured_rectangle(&chibiRectangle, &texturedShader, &chibiTexture, &g_Camera);
		
		color_renderer_submit_rectangle(
			(vec3) {0.5f, -0.5f, 0.0f},
			(vec2){1.0f, 1.0f}, 0,
	        (vec4) {0.9f, 0.0f, 0.0f, 1.0f},
		    (vec4) {0.7f, 0.6f, 0.6f, 1.0f},
		    (vec4) {0.5f, 0.6f, 0.8f, 1.0f},
		    (vec4) {0.4f, 0.4f, 0.9f, 1.0f});

		color_renderer_submit_rectangle(
		    (vec3) {1.5f, 1.5f, 0.0f},
			(vec2) {0.5f, 2.5f}, 0,
	        (vec4) {0.6f, 0.4f, 0.2f, 1.0f},
		    (vec4) {0.7f, 0.5f, 0.3f, 1.0f},
		    (vec4) {0.8f, 0.6f, 0.4f, 1.0f},
		    (vec4) {0.9f, 0.7f, 0.5f, 1.0f});

		color_renderer_submit_rectangle(
		    (vec3) {-1.5f, -1.5f, 0.0f},
			(vec2) {1.5f, 0.5f}, 0,
	        (vec4) {0.6f, 0.4f, 0.2f, 1.0f},
		    (vec4) {0.7f, 0.5f, 0.3f, 1.0f},
		    (vec4) {0.8f, 0.6f, 0.4f, 1.0f},
		    (vec4) {0.9f, 0.7f, 0.5f, 1.0f});
 
		f32 diff = 0.1f;
		f32 startx = -8.0f, starty = -8.0f;
		f32 endx = -2.0f, endy = -2.0f;
		for (f32 x = startx; x < endx; x += diff+0.005f)
		{
		  for (f32 y = starty; y < endy; y += diff+0.005f)
		  {
			color_renderer_submit_rectangle(
			    (vec3) {x, y, 0.0f},
				(vec2) {diff, diff}, 1,
				(vec4) {0.1f, 0.5f, 0.9f, 1.0f}, NULL, NULL, NULL);
		  }
		}
		
		color_renderer_flush(&batchedColorShader, &g_Camera);

#endif
		
		window_on_update(&window);
	}

	window_terminate();
	
	graphics_shader_delete_collection();

#if 1
	renderer_destroy_base_object(&hazelRectangle);
	renderer_destroy_base_object(&chibiRectangle);
#endif
	
	return 0;
}
