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

#define STOP() static i32 numberfordebugpurposes; scanf("%d", &numberfordebugpurposes)

#if HD == 1
f32 Width = 1280.0f; 
f32 Height = 720.0f;
#elif FULLHD == 1
f32 Width = 1920.0f; 
f32 Height = 1080.0f;
#else
f32 Width = 960.0f; 
f32 Height = 640.0f;
#endif

static i8 g_is_cursor_position_visible = 0;
static i8 g_is_cursor_enabled = 1;
static i8 g_is_freqency_visible = 0;
static u64 g_freqency;

f32 g_CameraSpeed = 4.0f;
OrthographicCamera g_Camera;
f32 g_ZoomLevel = 1.0f;
f32 g_AspectRatio;
f32 g_LastFrameTime = 0.0f;

//Textures
const char* shader_batched_texture_path = "CGLinux/resource/batched_texture_shader.glsl";
const char* texture_anime_chibi = "CGLinux/resource/anime_chibi.png";
const char* texture_cherno_hazel_logo = "CGLinux/resource/hazel.png";
const char* texture_hotline_miami = "CGLinux/resource/assets/textures/other/hotline_miami.png";

void 
window_mouse_scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset)
{
	if (yoffset < 0.0f || g_ZoomLevel > 0.1f)
	{
		g_ZoomLevel -= yoffset / 10;
	}

	char windowTitle[32];
	GFORMAT(windowTitle, "Demo %f", g_ZoomLevel);
	window_set_title(window, windowTitle);
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
window_resize_callback(GLFWwindow* window, u32 width, u32 height)
{
    //Camera stuff
	g_AspectRatio = width / height;
    //We can ResizeEvent.Invoke() here 
    //but we need EventSystmem for this
	orthographic_camera_set_projection(&g_Camera, 
		-g_AspectRatio * g_ZoomLevel, 
		 g_AspectRatio * g_ZoomLevel, 
		-g_ZoomLevel, g_ZoomLevel);
    //OpenGL stuff
	//glViewport(0, 0, width, height);
	renderer_set_viewport(width, height);
}

Window window;

char windowTitle[33];
vec4 triangleColor = { 0.2f, 0.5f, 1.0f, 1.0f };
vec4 redColor = { 0.8f, 0.1f, 0.1f, 1.0f };
vec4 yellowColor = { 1.0f, 1.0f, 0.0f, 1.0f };
vec4 blueColor = { 0.1f, 0.1f, 0.8f, 1.0f };
vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

Shader texturedShader;
Shader positionGradientShader;
Shader colorShader;
Shader batchedTextureShader;
	
Texture2D hazelLogoTexture;
Texture2D chibiTexture;
Texture2D hotlineMiamiTexture;

f32 tempTime;

void sandbox_on_update(f32 timestep);

void 
sandbox_on_attach()
{
	//app
	//seting stack size
    linux_set_application_stack(MB(100), MB(128));

	i32 isWindowCreated = window_create(&window, Width, Height, "Demo");
	if (isWindowCreated == -1) 
	{
		GLOG(RED("Can't create window!\n"));
		return;
	}
	
	window_set_vsync(1);
	window_set_scroll_callback(&window, window_mouse_scroll_callback);
	window_set_resize_callback(&window, window_resize_callback);
	GFORMAT(windowTitle, "Demo %f", g_ZoomLevel);
	window_set_title(window.GlfwWindow, windowTitle);
	
	//OpenGL
	i32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (status == 0)
	{
		GLOG(RED("Failed to init GLAD\n"));
		return;
	}
	GLOG(MAGNETA("OpenGL version %s\n"), glGetString(GL_VERSION));

	g_AspectRatio = Width / Height;
	g_Camera = orthographic_camera_create(
		-g_AspectRatio * g_ZoomLevel, 
		g_AspectRatio * g_ZoomLevel, 
		-g_ZoomLevel, g_ZoomLevel);

	batchedTextureShader =
	  graphics_shader_compile(
	  graphics_shader_load(shader_batched_texture_path));
	
	hazelLogoTexture = graphics_texture2d_create(texture_cherno_hazel_logo);
	chibiTexture = graphics_texture2d_create(texture_anime_chibi);
	hotlineMiamiTexture =
graphics_texture2d_create(texture_hotline_miami);
	  
	renderer_batch_init();
	
	f32 timestep;
	while (!window_should_close(&window))
	{
	    tempTime = (f32) glfwGetTime();
		timestep = tempTime - g_LastFrameTime;
		g_LastFrameTime = tempTime;

		sandbox_on_update(timestep);
		
		window_on_update(&window);
	}

	window_terminate();
	
	graphics_shader_delete_collection();

}

void sandbox_on_update(f32 timestep)
{
  if (window_is_key_pressed(&window, KEY_ESCAPE))
  {
	window_set_should_close(&window, 1);
  }

  if (window_is_key_pressed(&window, KEY_W))
  {
	  g_Camera.Position[1] += g_CameraSpeed * timestep;
  }
  else if (window_is_key_pressed(&window, KEY_S))
  {
	  g_Camera.Position[1] -= g_CameraSpeed * timestep;
  }
			
  if (window_is_key_pressed(&window, KEY_A))
  {
	  g_Camera.Position[0] -= g_CameraSpeed * timestep;
  }
  else if (window_is_key_pressed(&window, KEY_D))
  {
	  g_Camera.Position[0] += g_CameraSpeed * timestep;
  }
		
  if (window_is_key_pressed(&window, KEY_Q))
  {
	g_Camera.Rotation += 0.1f * timestep;
  }
  else if (window_is_key_pressed(&window, KEY_E))
  {
	g_Camera.Rotation -= 0.1f * timestep;
  }
		
  orthographic_camera_set_projection(&g_Camera, 
									 -g_AspectRatio*g_ZoomLevel, 
									  g_AspectRatio*g_ZoomLevel, 
									 -g_ZoomLevel,
									  g_ZoomLevel);
  orthographic_camera_recalculate_view_matrix(&g_Camera);

  renderer_clear((vec4) { 0.2f, 0.245f, 0.356f, 1.0f });

  renderer_submit_rectangle((vec3) {-1.5f, -0.5f, 0.0f}, (vec2) {1.0f, 1.0f}, &hazelLogoTexture, &batchedTextureShader, &g_Camera);
  renderer_submit_rectangle((vec3) {-1.5f, -2.5f, 0.0f}, (vec2) {2.0f, 2.0f}, &chibiTexture, &batchedTextureShader, &g_Camera);
  renderer_submit_rectangle((vec3) {-3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &chibiTexture, &batchedTextureShader, &g_Camera);
  renderer_submit_rectangle((vec3) {3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &hotlineMiamiTexture, &batchedTextureShader, &g_Camera);
  renderer_submit_rectangle((vec3) {3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &hotlineMiamiTexture, &batchedTextureShader, &g_Camera);
  
  renderer_submit_colored_rectangle((vec3) {1.0f, 1.0f, 0.0f}, (vec2) { 1.5f, 1.5f }, yellowColor);

  renderer_flush(&batchedTextureShader, &g_Camera);
}



typedef void (*OnAttach)();
typedef void (*OnUpdate)(f32 timestep);

typedef struct Layer {
  i32 Id;

  OnAttach OnAttach;
  OnUpdate OnUpdate;
} Layer;

static void layer_create(Layer* layer, OnAttach onAttach, OnUpdate onUpdate)
{
    layer->OnAttach = onAttach;
	layer->OnUpdate = onUpdate;
}

void App_OnUpdate(f32 timestep)
{
  GLOG("App_OnUpdate\n");
}

void App_OnAttach()
{
  
}

typedef struct App
{
  i8 IsMinimized;
  Layer* Layers;
} App;

static App s_App;

static void pseudo_app_add_layer(Layer layer)
{
  array_push(s_App.Layers, layer);
  layer.OnAttach();
}

static void pseudo_app_run()
{
  Layer layer1 = {};
  Layer layer2 = {};
  layer_create(&layer1, App_OnAttach, App_OnUpdate);
  layer_create(&layer2, App_OnAttach, App_OnUpdate);

  pseudo_app_add_layer(layer1);
  pseudo_app_add_layer(layer2);
  
  while (true)
  {
	  if (!s_App.IsMinimized)
	  {
	      for (i32 i = 0; i < array_len(s_App.Layers); i++)
	      {
	  	      s_App.Layers[i].OnUpdate(1.0f);
		  }	
	  }
	  
  }
}

static void pseudo_sandbox_onupdate(f32 timestep)
{
  //doing all sandbox stuff there
}

static void pseudo_sandbox_onattach()
{
  
}

static void pseudo_sandbox()
{
  Layer layer1 = {};
  layer_create(&layer1, pseudo_sandbox_onattach, pseudo_sandbox_onupdate);
  
  pseudo_app_add_layer(layer1);
}


static void EntryPoint()
{
  pseudo_app_run();
}
