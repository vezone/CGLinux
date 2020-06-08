#ifndef APPLICATION
#define APPLICATION

#include "Graphics/Window.h"
#include "Graphics/Renderer2D/Renderer2D.h"
#include "Graphics/KeyCodes.h"
#include "Utils/Logger.h"
#include "Platform/Linux/Linux.h"
#include "Event/Event.h"

typedef struct Layer
{
  i32 Id;
  void (*OnAttach)();
  void (*OnUpdate)(f32 timestep);
} Layer;

void application_init();
void application_start();
void application_on_event(Event* event);
void application_push_layer(Layer layer);


#endif
