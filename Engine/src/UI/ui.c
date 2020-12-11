#include "ui.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include <stdarg.h>
#include "nucklear.h"
#define NK_GLFW_GL3_IMPLEMENTATION
#include "nucklear_glfw_gl3.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

struct nk_context* g_Context;
struct nk_glfw g_Glfw;

void*
ui_get()
{
    return g_Context;
}

void
ui_on_attach(NativeWindow window)
{
    g_Context = nk_glfw3_init(&g_Glfw, window.GlfwWindow, NK_GLFW3_INSTALL_CALLBACKS);

    {
	struct nk_font_atlas *atlas;
	nk_glfw3_font_stash_begin(&g_Glfw, &atlas);
	nk_glfw3_font_stash_end(&g_Glfw);
    }
}

//paste code from nk_glfw3 to this function
#include "Utils/Logger.h"
void
ui_on_event(Event* event)
{
    //NOTE(vez): empty for now
    i32 isHovered = nk_window_is_any_hovered(g_Context);
    if (isHovered)
    {
	if (event->Category == MouseCategory)
	{
	    if (event->Type == MouseButtonPressed)
	    {
		event->IsHandled = 1;
	    }
	    else if (event->Type == MouseButtonReleased)
	    {
		event->IsHandled = 1;
	    }
	}
	else if (event->Category == KeyCategory)
	{
	    if (event->Type == KeyPressed || event->Type == KeyRepeatPressed || event->Type == KeyRealeased || event->Type == KeyTyped)
	    {
		event->IsHandled = 1;
	    }
	}
    }
}

void
ui_on_destoy()
{
    nk_glfw3_shutdown(&g_Glfw);
}

void ui_begin()
{
    nk_glfw3_new_frame(&g_Glfw);
}

void ui_end()
{
    nk_glfw3_render(&g_Glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}
