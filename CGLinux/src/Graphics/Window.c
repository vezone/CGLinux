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

    glfwMakeContextCurrent(window->GlfwWindow);
	glfwSwapInterval(1);

    return(1);
}

i32
window_is_key_pressed(Window* window, i32 key)
{
    i32 state = glfwGetKey(window->GlfwWindow, key);
    return(state == GLFW_PRESS || state == GLFW_REPEAT);        
}

i32 
window_is_mouse_pressed(Window* window, i32 key)
{
    i32 state = glfwGetMouseButton(window->GlfwWindow, key);
    return(state == GLFW_PRESS);
}

void 
window_on_update(Window* window)
{
    glfwSwapBuffers(window->GlfwWindow);
	glfwPollEvents();
}