#ifndef EDITOR_APPLICATION
#define EDITOR_APPLICATION

#include "Graphics/Window.h"
#include "Graphics/KeyCodes.h"
#include "Utils/Logger.h"
#include "Event/Event.h"
#include "Platform/Linux/Linux.h"

typedef struct Layer
{
  void (*OnAttach)(NativeWindow window);
  void (*OnUpdate)(f32 timestep);
  void (*OnEvent)(Event* event);
  void (*OnDestoy)();
} Layer;

typedef struct Application {
  i8 IsMinimized;
  i8 IsRunning;
  char* EventTypeToString[32];
  Layer* Layers;
  NativeWindow Window;
} Application;

Application* editor_get();
void editor_push_layer(Layer layer);
void editor_init(u32 width, u32 height, const char* name);
void editor_start();
void editor_on_event(Event* event);

#endif
