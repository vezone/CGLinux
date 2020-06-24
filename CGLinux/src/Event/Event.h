#ifndef EVENT
#define EVENT

#include "Utils/Types.h"

/*
  TODO(vez): remove this code in the future
 */
//Category for events ?
typedef enum EventType
{
    None = 0,
    WindowClosed, WindowResized, WindowFocused, WindowUnfocused, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyRepeatPressed, KeyRealeased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
} EventType;

typedef enum EventCategory
{
  NoneCategory = 0,
  WindowCategory,
  AppCategory,
  KeyCategory,
  MouseCategory
} EventCategory;

void event_init_table(char** EventTypeToString, i32 count);

typedef struct Event
{
  i8 IsHandled;
  EventType Type;
  EventCategory Category;
} Event;

typedef struct KeyPressedEvent 
{
  Event Base;
  i32 KeyCode;
  i32 RepeatCount;
} KeyPressedEvent;

typedef struct KeyReleasedEvent 
{
  Event Base;
  i32 KeyCode;
} KeyReleasedEvent;

typedef struct WindowResizedEvent
{
  Event Base;
  i32 Width;
  i32 Height;
} WindowResizedEvent;

typedef struct MouseMovedEvent
{
  Event Base;
  f32 X;
  f32 Y;
} MouseMovedEvent;

typedef struct MouseScrolledEvent
{
  Event Base;
  f64 XOffset;
  f64 YOffset;
} MouseScrolledEvent;

typedef struct MouseButtonEvent
{
  Event Base;
  i32 MouseCode;
} MouseButtonEvent;

// NOTE(vez): for this type event don't use struct
// only Event .Type =  WindowClosedEvent

#endif
