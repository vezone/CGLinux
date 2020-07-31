#include "App/Application.h"
//#include "Utils/Types.h"
//#include "Utils/Logger.h"
//#include "Math/Vector2Test.h"

#define ALLOCATOR_TEST 0
#define VECTIR2_TEST 0

/*
  TODO:
  *  use only header guard
  *  rebuild arch
  *  tiling factor for textures
  [*] render2d statistics

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


extern void create_user_application();

int main(int argc, char** argv)
{
    int temp;
    Layer layer;

    application_init(1280, 720, "Demo");
    create_user_application();
    application_start();

#if ALLOCATOR_TEST == 1
    bies_allocator_test();
#endif

#if VECTIR2_TEST == 1
    vector2f_test();
#endif

#if CIMGUI_TEST == 1
    imgui_test();
#endif

    return 0;
}
