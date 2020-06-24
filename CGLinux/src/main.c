#include "App/Sandbox.h"
#include "App/Application.h"
#include "Utils/Types.h"
#include "Utils/Logger.h"

/*
  TODO:
  * use only ansi c way of pragma once
  * rebuild arch

  App + Event:
    451
  Graphics (only, without Renderer):
    1 652
  Renderer2D:
    652
  Platform:
    32
  Utils:
    539
  
  3 326
  
*/

int main()
{
    i32 temp;
	Layer layer;

	application_init(1280, 720, "Demo");
	layer.OnAttach = sandbox_on_attach;
	layer.OnUpdate = sandbox_on_update;
	layer.OnEvent = sandbox_on_event;
	layer.OnDestoy = sandbox_on_destroy;
	application_push_layer(layer);

	application_start();
	
	return 0;
}
