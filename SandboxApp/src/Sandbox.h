#ifndef SANDBOX
#define SANDBOX

#include <Engine.h>

i32 sandbox_start();
void sandbox_on_attach(Window window);
void sandbox_on_update(f32 timestep);
void sandbox_on_event(Event* event);

static void
sandbox_on_destroy()
{
  graphics_shader_delete_collection();
}
#endif
