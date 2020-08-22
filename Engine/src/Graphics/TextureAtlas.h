#ifndef TEXTURE_ATLAS
#define TEXTURE_ATLAS

#include "Graphics/Texture2D.h"
#include "Utils/Types.h"

typedef struct TextureAtlas
{
    i32 TextureWidth;
    i32 TextureHeight;
    Texture2D* MainTexture;
} TextureAtlas;

TextureAtlas*
texture_atlas_register(Texture2D* textureBuffer, const char* path);

//Binding Atlas main Texture
//TextureAtlas* Atlas = texture_atlas_register(Texture2D* textureBuffer, const char* path);
//TextureCoord tex1 = texture_atlas_get_texture(1, 1);
//TextureCoord tex2 = texture_atlas_get_texture(1, 2);

//renderer_draw_atlas_rectangle(tex1, (glm_vec2){1.5f, 1.5f}, (glm_vec2){1.f, 1.f, 0.0f});
//renderer_draw_atlas_rectangle(tex2, ...);

#endif
