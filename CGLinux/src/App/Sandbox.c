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

//Textures
const char* shader_batched_texture_path = "CGLinux/resource/batched_texture_shader.glsl";
const char* texture_anime_chibi = "CGLinux/resource/anime_chibi.png";
const char* texture_cherno_hazel_logo = "CGLinux/resource/hazel.png";
const char* texture_hotline_miami = "CGLinux/resource/assets/textures/other/hotline_miami.png";

Window g_Window;

OrthographicCamera g_Camera;
f32 g_LastFrameTime = 0.0f;

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

void 
sandbox_on_attach(Window window)
{
    g_Window = window;
	f32 aspectRatio = Width / Height;
	f32 zoomLevel = 1.0f;
	g_Camera = orthographic_camera_create(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
	g_Camera.AspectRatio = aspectRatio;
	g_Camera.ZoomLevel = zoomLevel;
	g_Camera.Speed = 5.0f;
	
	batchedTextureShader =
	  graphics_shader_compile(
	  graphics_shader_load(shader_batched_texture_path));
	
	hazelLogoTexture = graphics_texture2d_create(texture_cherno_hazel_logo);
	chibiTexture = graphics_texture2d_create(texture_anime_chibi);
	hotlineMiamiTexture =
graphics_texture2d_create(texture_hotline_miami);
	  
	renderer_batch_init(&batchedTextureShader, &g_Camera);
}

void sandbox_on_update(f32 timestep)
{
  orthographic_camera_on_update(&g_Camera, &g_Window, timestep);

  renderer_clear((vec4) { 0.2f, 0.245f, 0.356f, 1.0f });

  renderer_submit_rectangle((vec3) {-1.5f, -0.5f, 0.0f}, (vec2) {1.0f, 1.0f}, &hazelLogoTexture);
  renderer_submit_rectangle((vec3) {-1.5f, -2.5f, 0.0f}, (vec2) {2.0f, 2.0f}, &chibiTexture);
  renderer_submit_rectangle((vec3) {-3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &chibiTexture);
  renderer_submit_rectangle((vec3) {3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &hotlineMiamiTexture);
  renderer_submit_rectangle((vec3) {3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &hotlineMiamiTexture);

  renderer_submit_colored_rectangle((vec3) {1.0f, 1.0f, 0.0f}, (vec2) { 1.5f, 1.5f }, yellowColor);

  
  #if 1
  static i32 flag = 1;
  i32 counter = 0;
  for (f64 y = 2.5; y < 5.5; y+=0.011)
  for (f64 x = 2.5; x < 5.5; x+=0.011)
  {
	++counter;
	renderer_submit_rectangle((vec3) {x, y, 0.0f}, (vec2) {0.01f, 0.01f}, &chibiTexture);
  }

  if (flag)
  {
	GLOG("Counter: %d\n", counter);
	flag = 0;
  }
  #endif
  
  renderer_flush();
}

void
sandbox_on_event(Event* event)
{
  if (event->IsHandled == 1)
  {
	  return;
  }

  orthographic_camera_on_event(&g_Camera, event);
  
  if (event->Category == KeyCategory)
  {
	KeyPressedEvent* keyEvent = (KeyPressedEvent*) event;
	if (window_is_key_pressed(&g_Window, KEY_ESCAPE))
	{
	  window_set_should_close(&g_Window, 1);
	}

	event->IsHandled = 1;
  }
  else if (event->Category == MouseCategory)
  {
	char windowTitle[32];

	if (event->Type == MouseButtonPressed)
	{
	  MouseButtonEvent* mevent = (MouseButtonEvent*) event;
	  if (mevent->MouseCode == MOUSE_BUTTON_1)
	  {
		  g_Camera.ZoomLevel = 1.0f;
	  }
	}

	GFORMAT(windowTitle, "Demo %f", g_Camera.ZoomLevel);
	window_set_title(&g_Window, windowTitle);

	event->IsHandled = 1;
  }

}

