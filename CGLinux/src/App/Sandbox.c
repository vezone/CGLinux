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
const char* texture_cherno_hazel_logo = "CGLinux/resource/hazel.png";
const char* texture_hotline_miami = "CGLinux/resource/assets/textures/other/hotline_miami.png";

typedef struct TexturedQuadVertex
{
  vec3 Position;
  vec2 TexturePosition;
  f32 TextureId;
} TexturedQuadVertex;

typedef struct TexturedQuad
{
  TexturedQuadVertex vertex[4];
} TexturedQuad;

#define MaxObjectToDraw 10000
#define MaxTextureSlots 32
#define QuadVerticesCount ((3 + 2 + 1) * 4) 
#define VerticesCount (MaxObjectToDraw * QuadVerticesCount)
#define IndicesCount (MaxObjectToDraw * 6)
#define TexturedDataSize (VerticesCount * sizeof(f32))

typedef struct TexturedBatchRenderer2DData
{
  u32 DataCount;
  f32 Data[VerticesCount];

  u32 IndexCount;
  u32 Indices[IndicesCount];

  u32 NextTextureIndex;
  Texture2D Textures[32];
  VertexArray Vao;
  Shader Shader;
  mat4 Transform;
} TexturedBatchRenderer2DData;

TexturedBatchRenderer2DData TextureRenderer2DData =
{
	.DataCount = 0,
	.IndexCount = 0,
	.NextTextureIndex = 0
};

void
textured_renderer_flush(Shader* shader, OrthographicCamera* camera);

static void
convert_quad_to_array(f32* destination, TexturedQuad* source, u32 start_index)
{
	i32 s = 0;
    i32 i = start_index;
	i32 number_of_vertices = start_index + (4 * (3 + 2 + 1));
	for ( ;i < number_of_vertices; )
	{
	   TexturedQuadVertex vertex = source->vertex[s];
	   s++;
	   
	   destination[i++] = vertex.Position[0];
	   destination[i++] = vertex.Position[1];
	   destination[i++] = vertex.Position[2];

	   destination[i++] = vertex.TexturePosition[0];
	   destination[i++] = vertex.TexturePosition[1];

	   destination[i++] = (f32) vertex.TextureId;
	}
}

static void
textured_quad_create(TexturedQuad* quad, vec3 position, vec2 size, i32 textureId)
{
	quad->vertex[0].Position[0] = position[0];
	quad->vertex[0].Position[1] = position[1];
	quad->vertex[0].Position[2] = position[2];
	
	quad->vertex[1].Position[0] = position[0];
	quad->vertex[1].Position[1] = position[1] + size[1];
	quad->vertex[1].Position[2] = position[2];
	
	quad->vertex[2].Position[0] = position[0] + size[0];
	quad->vertex[2].Position[1] = position[1] + size[1];
	quad->vertex[2].Position[2] = position[2];
	
	quad->vertex[3].Position[0] = position[0] + size[0];
	quad->vertex[3].Position[1] = position[1];
	quad->vertex[3].Position[2] = position[2];

	quad->vertex[0].TexturePosition[0] = 0;
	quad->vertex[0].TexturePosition[1] = 0;
	quad->vertex[1].TexturePosition[0] = 0;
	quad->vertex[1].TexturePosition[1] = 1;
	quad->vertex[2].TexturePosition[0] = 1;
	quad->vertex[2].TexturePosition[1] = 1;
	quad->vertex[3].TexturePosition[0] = 1;
	quad->vertex[3].TexturePosition[1] = 0;

	quad->vertex[0].TextureId = (f32) textureId;
	quad->vertex[1].TextureId = (f32) textureId;
	quad->vertex[2].TextureId = (f32) textureId;
	quad->vertex[3].TextureId = (f32) textureId;
}

void
textured_renderer_batch_init()
{
	VertexBuffer vbo = {};
	graphics_vertex_buffer_allocate(
	    &vbo, TexturedDataSize);
	graphics_vertex_buffer_bind(&vbo);
	
	graphics_vertex_buffer_add_layout(&vbo, 0, Float3);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float2);
	graphics_vertex_buffer_add_layout(&vbo, 0, Float1);
	
	IndexBuffer ibo = {};
	fill_indices_array(TextureRenderer2DData.Indices, IndicesCount);
	graphics_index_buffer_create(&ibo, TextureRenderer2DData.Indices, IndicesCount);
	graphics_index_buffer_bind(&ibo);

	graphics_vertex_array_create(&TextureRenderer2DData.Vao);
	graphics_vertex_array_add_vbo(&TextureRenderer2DData.Vao, vbo);
	graphics_vertex_array_add_ibo(&TextureRenderer2DData.Vao, ibo);
	graphics_vertex_array_bind(&TextureRenderer2DData.Vao);
	
	glm_mat4_identity(TextureRenderer2DData.Transform);
}

void
textured_renderer_submit_rectangle(vec3 position, vec2 size, Texture2D* texture, Shader* shader, OrthographicCamera* camera)
{
    i32 textureId;
    if (TextureRenderer2DData.NextTextureIndex < 31)
	{
	  
	  i8 isAlreadyInArray = -1;
	  for (i32 i = 0; i < TextureRenderer2DData.NextTextureIndex; i++)
	  {
		u32 id = TextureRenderer2DData.Textures[i].RendererID;
		if (id == texture->RendererID)
		{
		  isAlreadyInArray = i;
		  break;
		}
	  }

	  if (isAlreadyInArray != -1)
	  {
		textureId = isAlreadyInArray;
	  }
	  else
	  {
		textureId = TextureRenderer2DData.NextTextureIndex;
		TextureRenderer2DData.Textures[
            TextureRenderer2DData.NextTextureIndex] = *texture;
		++TextureRenderer2DData.NextTextureIndex;	  
	  }
	}
	else
	{
	  textured_renderer_flush(shader, camera);
	  textureId = 0;
	  TextureRenderer2DData.DataCount = 0;
	  TextureRenderer2DData.IndexCount = 0;
	  TextureRenderer2DData.NextTextureIndex = 0;
	}
  
    TexturedQuad quad = {};
    textured_quad_create(&quad, position, size, textureId);

	convert_quad_to_array(TextureRenderer2DData.Data, &quad, TextureRenderer2DData.DataCount);

	TextureRenderer2DData.DataCount  += (4 * 6);
	TextureRenderer2DData.IndexCount += 6;
}

void
textured_renderer_flush(Shader* shader, OrthographicCamera* camera)
{
	graphics_shader_bind(shader);	
	graphics_vertex_array_bind(&(TextureRenderer2DData.Vao));

	i32 textureIndices[32];
	for (i32 i = 0; i < TextureRenderer2DData.NextTextureIndex; i++)
	{
	  textureIndices[i] = i;
	}
	
	for (i32 i = 0; i < TextureRenderer2DData.NextTextureIndex; i++)
	{
	  graphics_texture2d_bind(&(TextureRenderer2DData.Textures[i]), i);
	}

	u32 size = TextureRenderer2DData.DataCount * sizeof(f32); 
	graphics_vertex_buffer_set_data(
   		TextureRenderer2DData.Vao.VertexBuffer,
		TextureRenderer2DData.Data, size);

	graphics_shader_set_mat4(shader,
		"u_ViewProjection", 1, 0,
		camera->ViewProjectionMatrix[0]); 
	graphics_shader_set_int1(shader, "u_Textures", TextureRenderer2DData.NextTextureIndex, textureIndices);
	
	glDrawElements(GL_TRIANGLES,
				   TextureRenderer2DData.IndexCount,
				   GL_UNSIGNED_INT,
				   NULL);

	TextureRenderer2DData.DataCount  = 0;
	TextureRenderer2DData.IndexCount = 0;
	TextureRenderer2DData.NextTextureIndex = 0;
}

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
	g_AspectRatio = width / Width;
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

Shader texturedShader;
Shader positionGradientShader;
Shader colorShader;
Shader batchedColorShader;
Shader batchedTextureShader;
	
Texture2D hazelLogoTexture;
Texture2D chibiTexture;
Texture2D hotlineMiamiTexture;

BaseObject chibiRectangle;
BaseObject hazelRectangle;
i32 movementControlState;
f32 tempTime;

void sandbox_on_update();

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

	//OpenGL
	i32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (status == 0)
	{
		GLOG(RED("Failed to init GLAD\n"));
		return;
	}
	GLOG(MAGNETA("OpenGL version %s\n"), glGetString(GL_VERSION));

	g_Camera = orthographic_camera_create(
		-g_AspectRatio *g_ZoomLevel, 
		g_AspectRatio *g_ZoomLevel, 
		-g_ZoomLevel, g_ZoomLevel);
	g_AspectRatio = Width / Height;

	texturedShader = graphics_shader_compile(		graphics_shader_load("CGLinux/resource/simple_texture_shader.glsl"));
	positionGradientShader = graphics_shader_compile(		graphics_shader_load("CGLinux/resource/simple_shader.glsl"));
	colorShader = graphics_shader_compile(		graphics_shader_load("CGLinux/resource/simple_color_shader.glsl"));
	batchedColorShader = graphics_shader_compile(		graphics_shader_load("CGLinux/resource/simple_batched_color_shader.glsl"));
	batchedTextureShader = graphics_shader_compile(
	    graphics_shader_load(
		"CGLinux/resource/batched_texture_shader.glsl"));
	
	hazelLogoTexture = graphics_texture2d_create(texture_cherno_hazel_logo);
	chibiTexture = graphics_texture2d_create(texture_anime_chibi);
	hotlineMiamiTexture =
graphics_texture2d_create(texture_hotline_miami);
	  
	chibiRectangle = renderer_create_textured_rectangle(-0.5f, -0.5f);
	hazelRectangle = renderer_create_textured_rectangle(-0.5f, -0.5f);
	
	color_renderer_batch_init();	
	textured_renderer_batch_init();
	GFORMAT(windowTitle, "Demo %f", g_ZoomLevel);
	window_set_title(window.GlfwWindow, windowTitle);
	
    movementControlState = 1;
	while (!window_should_close(&window))
	{
	    sandbox_on_update();
		
		window_on_update(&window);
	}

	window_terminate();
	
	graphics_shader_delete_collection();

#if 1
	renderer_destroy_base_object(&hazelRectangle);
	renderer_destroy_base_object(&chibiRectangle);
#endif
}

void sandbox_on_update()
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
		
  orthographic_camera_set_projection(&g_Camera, 
									 -g_AspectRatio*g_ZoomLevel, 
									  g_AspectRatio*g_ZoomLevel, 
									 -g_ZoomLevel,
									  g_ZoomLevel);
  orthographic_camera_recalculate_view_matrix(&g_Camera);
	
  glClearColor(0.2f, 0.345f, 0.456f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
		
#if DRAW_BASE_SCENE == 1

  //renderer_draw_textured_rectangle(&hazelRectangle, &texturedShader, &hazelLogoTexture, &g_Camera);
  //renderer_draw_textured_rectangle(&chibiRectangle, &texturedShader, &chibiTexture, &g_Camera);
		
  color_renderer_submit_rectangle(
      (vec3) {0.5f, -0.5f, 0.0f},
      (vec2){1.0f, 1.0f}, 0,
      (vec4) {0.85f, 0.05f, 0.05f, 1.0f},
      (vec4) {0.7f, 0.6f, 0.6f, 1.0f},
      (vec4) {0.5f, 0.6f, 0.8f, 1.0f},
      (vec4) {0.05f, 0.05f, 0.85f, 1.0f});

  color_renderer_submit_rectangle(
	  (vec3) {1.5f, 1.5f, 0.0f},
	  (vec2) {0.5f, 2.5f}, 0,
	  (vec4) {0.6f, 0.4f, 0.2f, 1.0f},
	  (vec4) {0.545f, 0.455f, 0.3f, 1.0f},
	  (vec4) {0.545f, 0.455f, 0.3f, 1.0f},
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

  textured_renderer_submit_rectangle((vec3) {-1.5f, -0.5f, 0.0f}, (vec2) {1.0f, 1.0f}, &hazelLogoTexture, &batchedTextureShader, &g_Camera);
  textured_renderer_submit_rectangle((vec3) {-1.5f, -2.5f, 0.0f}, (vec2) {2.0f, 2.0f}, &chibiTexture, &batchedTextureShader, &g_Camera);
  textured_renderer_submit_rectangle((vec3) {-3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &chibiTexture, &batchedTextureShader, &g_Camera);
  textured_renderer_submit_rectangle((vec3) {3.0f, -2.5f, 0.0f}, (vec2) {1.5f, 1.5f}, &hotlineMiamiTexture, &batchedTextureShader, &g_Camera);
  
  textured_renderer_flush(&batchedTextureShader, &g_Camera);
  
#endif

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
