#ifndef APPLICATION
#define APPLICATION

#include "Graphics/Window.h"
#include "Graphics/KeyCodes.h"
#include "Utils/Logger.h"
#include "Event/Event.h"
#include "Platform/Linux/Linux.h"

typedef struct Layer
{
  void (*OnAttach)(Window window);
  void (*OnUpdate)(f32 timestep);
  void (*OnEvent)(Event* event);
  void (*OnDestoy)();
} Layer;

typedef struct Application {
  i8 IsMinimized;
  i8 IsRunning;
  char* EventTypeToString[32];
  Layer* Layers;
  Window Window;
} Application;

void application_push_layer(Layer layer);
void application_init(u32 width, u32 height, const char* name);
void application_start();
void application_on_event(Event* event);

#endif
