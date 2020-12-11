#include "App/Application.h"

/*
  TODO:
  *  tiling factor for textures
  *  remove GLCall for every gl function
  *  remove all "changes meaning errors"

  4 800
*/


extern void create_user_application();

int main(int argc, char** argv)
{
    int temp;
    Layer layer;

    application_init(1280, 720, "Demo");
    create_user_application();
    application_start();

    return 0;
}
