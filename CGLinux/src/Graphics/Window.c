#include "Window.h"

#include "Utils/Logger.h"

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
	
    return(1);
}
