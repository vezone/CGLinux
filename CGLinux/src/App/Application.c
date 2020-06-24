#include "Application.h"
#include "Graphics/Renderer2D/Renderer2D.h"

Application g_Application;

void
application_push_layer(Layer layer)
{
    array_push(g_Application.Layers, layer);
	layer.OnAttach(g_Application.Window);
}

static void 
window_resize_callback(GLFWwindow* window, i32 width, i32 height)
{
	renderer_set_viewport(width, height);
}

void application_init(u32 width, u32 height, const char* name)
{
    //create window there
    //all stuff
    //
	g_Application.IsMinimized = 0;
    g_Application.IsRunning = 1;
	
    linux_set_application_stack(MB(500), MB(528));
    event_init_table(g_Application.EventTypeToString, 32);
	
    i32 isWindowCreated = window_create(&g_Application.Window, width, height, "Demo", application_on_event);
	if (isWindowCreated == -1) 
	{
		GERROR("Can't create window!\n");
		return;
	}
	
	window_set_vsync(1);
	//window_set_resize_callback(&g_Application.Window, window_resize_callback);
	
	//GFORMAT(windowTitle, "Demo %f", g_Camera.ZoomLevel);
	//window_set_title(&window, windowTitle);
	
	//OpenGL
	i32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (status == 0)
	{
		GERROR("Failed to init GLAD\n");
		return;
	}
	GLOG(MAGNETA("OpenGL version %s\n"), glGetString(GL_VERSION));
}

void application_start()
{
	f32 tempTime;
	f32 timeStep;
	f32 lastFrameTime;
	i32 layersCount = array_len(g_Application.Layers);
	while (!window_should_close(&g_Application.Window))
	{
	  tempTime = (f32) glfwGetTime();
	  timeStep = tempTime - lastFrameTime;
	  lastFrameTime = tempTime;

	  if (!g_Application.IsMinimized)
	  {
		  for (i32 l = 0; l < layersCount; l++)
		  {
		      g_Application.Layers[l].OnUpdate(timeStep);
		  }

		  window_on_update(&g_Application.Window);
	  }
	}

	for (i32 l = 0; l < layersCount; l++)
	{
		g_Application.Layers[l].OnDestoy();
	}
	
	
	window_terminate();
}

void
application_on_event(Event* event)
{
  if (event->Category == WindowCategory)
  {
	if (event->Type == WindowResized)
	{
	    WindowResizedEvent* wevent = (WindowResizedEvent*) event; 
		renderer_set_viewport(wevent->Width, wevent->Height);
	}
  }
  
  i32 length = array_len(g_Application.Layers);
  for (i32 l = 0; l < length; l++)
  {
	Layer layer = g_Application.Layers[l];
	layer.OnEvent(event);
  }
}
