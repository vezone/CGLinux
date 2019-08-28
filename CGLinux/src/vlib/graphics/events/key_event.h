#pragma once

#include "event.h"
#include "../../core/vtypes.h"

typedef struct 
{
    event base;
    int32 keycode;
} key_pressed_event;

void event_callback(event* e)
{
    switch(e->type)
    {
        case KeyPressed:
        {
            key_pressed_event kpevent = *((key_pressed_event*)e);
            printf("key code = %d\n", kpevent.keycode);
            break;
        }
    }
}

void key_event_test()
{
    key_pressed_event kpevent;
    kpevent.base.is_handled = 0;
    kpevent.base.type = KeyPressed;
    kpevent.keycode = 34;
    event_callback(&kpevent.base);
}