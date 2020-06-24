#pragma once

#include <GLFW/glfw3.h>

#include "Event/Event.h"
#include "Utils/Types.h"

#define window_get_frequency() glfwGetTimerFrequency()
#define window_get_cursor_position(window, xPos, yPos) glfwGetCursorPos((window)->GlfwWindow, xPos, yPos);
#define window_set_drop_callback(window, callback) glfwSetDropCallback((window)->GlfwWindow, callback)

typedef struct Window {
    u32 Width;
    u32 Height;
    const char* Title;
    void (*OnEvent)(Event* event);
    GLFWwindow* GlfwWindow;
} Window;

static i32
window_should_close(Window* window)
{
  return glfwWindowShouldClose(window->GlfwWindow);
}

static void
window_set_should_close(Window* window, i8 shouldClose)
{
  glfwSetWindowShouldClose(window->GlfwWindow, shouldClose);
}

static void
window_terminate()
{
  glfwTerminate();
}

static void
window_set_title(Window* window, const char* title)
{
  glfwSetWindowTitle(window->GlfwWindow, title); 
}

static void
window_set_resize_callback(Window* window, void (*callback) (GLFWwindow* window, i32 width, i32 height))
{
  glfwSetWindowSizeCallback(window->GlfwWindow, callback);
}

i32
window_create(Window* window, u32 width, u32 height, const char* tittle, void (*onEvent)(Event* event));

static i32
window_is_key_pressed(Window* window, i32 key)
{
    i32 state = glfwGetKey(window->GlfwWindow, key);
    return(state == GLFW_PRESS || state == GLFW_REPEAT);        
}

static i32 
window_is_mouse_pressed(Window* window, i32 key)
{
    i32 state = glfwGetMouseButton(window->GlfwWindow, key);
    return(state == GLFW_PRESS);
}

static void
window_set_vsync(i32 isVsync)
{
	glfwSwapInterval(isVsync);
}

static void 
window_on_update(Window* window)
{
    glfwSwapBuffers(window->GlfwWindow);
	glfwPollEvents();
}
