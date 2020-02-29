#pragma once

#include "Utils/Types.h"

typedef struct Texture2D {
    u32 RendererID;
    i32 Width;
    i32 Height;
    i32 BitsPerPixel;
    const char* Path;
} Texture2D;

Texture2D 
graphics_texture2d_create(const char* path);
void
graphics_texture2d_bind(Texture2D* texture, u32 slot);
void
graphics_texture2d_unbind();