#pragma once

#include "Utils/Types.h"

typedef struct Texture2D {
    u32 RendererID;
    u32 Width;
    u32 Height;
    u32 Channels;
    u32 Slot;
    const char* Path;
} Texture2D;

Texture2D 
graphics_texture2d_create(const char* path);
void
graphics_texture2d_bind(Texture2D* texture, u32 slot);
void
graphics_texture2d_unbind(Texture2D* texture);
void
graphics_texture2d_delete(Texture2D* texture);