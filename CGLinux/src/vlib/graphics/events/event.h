#pragma once

typedef enum event_type
{
    None = 0,
    WindowClosed, WindowResized, WindowFocused, WindowUnfocused, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyRealeased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
} event_type;

typedef struct event
{
    int8 is_handled;
    event_type type;
} event;