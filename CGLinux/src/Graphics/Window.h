#pragma once

#include <GLFW/glfw3.h>
#include "Utils/Types.h"

typedef struct Window {
    u32 Width;
    u32 Height;
    const char* Title;
    GLFWwindow* GlfwWindow;
} Window;

#define window_should_close(window) glfwWindowShouldClose((window)->GlfwWindow)
#define window_set_should_close(window, x) glfwSetWindowShouldClose((window)->GlfwWindow, x)
#define window_terminate() glfwTerminate()
#define window_get_frequency() glfwGetTimerFrequency()
#define window_get_cursor_position(window, xPos, yPos) glfwGetCursorPos((window)->GlfwWindow, xPos, yPos);
#define window_set_title(window, title) glfwSetWindowTitle(window, title)	
//rework it in a future
#define window_set_scroll_callback(window, callback) glfwSetScrollCallback((window)->GlfwWindow, callback)
#define window_set_drop_callback(window, callback) glfwSetDropCallback((window)->GlfwWindow, callback)
#define window_set_resize_callback(window, callback) glfwSetWindowSizeCallback((window)->GlfwWindow, callback)

i32
window_create(Window* window, u32 width, u32 height, const char* tittle);

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
