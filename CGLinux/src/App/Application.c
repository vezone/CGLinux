#include "Application.h"

i8 IsMinimized = 0;
Layer* Layers;
static Window window;
char* EventTypeToString[32];

void application_on_event(Event* event)
{
  GLOG("event: %s\n", EventTypeToString[event->Type]);
}

void application_init(u32 width, u32 height, const char* name)
{
  //create window there
  //all stuff
  //
  linux_set_application_stack(MB(500), MB(528));
  event_init_table(EventTypeToString, 32);
  
  i32 isWindowCreated = window_create(&window, width, height, name);
  if (isWindowCreated == -1) 
  {
	  GERROR("Can't create window!\n");
	  return;
  }
  //window_on_event_function = application_on_event; 
  window_set_vsync(1);
  
  //OpenGL
  i32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  if (status == 0)
  {
	GERROR("Failed to init GLAD\n");
	return;
  }
  GLOG(MAGNETA("OpenGL version %s\n"), glGetString(GL_VERSION));
}

void application_push_layer(Layer layer)
{
  array_push(Layers, layer);
  layer.OnAttach();
}

void application_start()
{
    i8 isWorking = 1;
	f32 tempTime;
	f32 timeStep;
	f32 lastFrameTime;

	vec4 backgroundColor = { 0.2f, 0.345f, 0.456f, 1.0f };
	
	while (isWorking)
	{
	  tempTime = (f32) glfwGetTime();
	  timeStep = tempTime - lastFrameTime;
	  lastFrameTime = tempTime;

	  if (window_is_key_pressed(&window, KEY_ESCAPE))
	  {
		window_set_should_close(&window, 1);
		return;
	  }
	  
	  renderer_clear(backgroundColor);
	  
	  if (!IsMinimized)
	  {
		  for (i32 i = 0; i < array_len(Layers); i++)
		  {
		      Layers[i].OnUpdate(timeStep);
		  }
	  }

	  return;
	  
	}
}
