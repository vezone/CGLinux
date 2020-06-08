#include "Window.h"
#include "Utils/Logger.h"
#include "Event/Event.h"

static void
internal_scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset)
{
  MouseScrolledEvent event = {};
  event.Base.IsHandled = 0;
  event.Base.Type = MouseScrolled;
  event.XOffset = xoffset;
  event.YOffset = yoffset;

  //window_on_event_function(&event);
}

static void
internal_window_size_callback(GLFWwindow* window, i32 width, i32 height)
{
  WindowResizedEvent event = {};
  event.Base.IsHandled = 0;
  event.Base.Type = WindowResized;
  event.Width = width;
  event.Height = height;

  //window_on_event_function(&event);
}

i32
window_create(Window* window, u32 width, u32 height, const char* tittle)
{
    if (!glfwInit())
	{
		GLOG(RED("GLFW is not initialized!\n"));
		return(-1);
	}

    i32 major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	GLOG(MAGNETA("GLFW version: %d.%d.%d\n"), major, minor, revision);

    window->Width = width;
    window->Height = height;
    window->Title = tittle;
    window->GlfwWindow = glfwCreateWindow(width, height, tittle, 0, 0);
	//glfwSetInputMode(window->GlfwWindow, GLFW_STICKY_KEYS, 0);
	
    glfwMakeContextCurrent(window->GlfwWindow);

	glfwSetScrollCallback(window->GlfwWindow, internal_scroll_callback);
	glfwSetWindowSizeCallback(window->GlfwWindow, internal_window_size_callback);
	
    return(1);
}
