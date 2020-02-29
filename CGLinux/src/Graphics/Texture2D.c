#include "Texture2D.h"

#include <glad/glad.h>

#include "Utils/Array.h"
#include "Utils/stb_image.h"

u32* TexturesCollection = NULL;

Texture2D 
graphics_texture2d_create(const char* path)
{
    Texture2D texture = {
        .Path = path
    };

    stbi_set_flip_vertically_on_load(1);
    void* data = stbi_load(path, &texture.Width, &texture.Height, &texture.BitsPerPixel, 4);

    glGenTextures(1, &texture.RendererID);
    glBindTexture(GL_TEXTURE_2D, texture.RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x2900);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x2900);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
        texture.Width, texture.Height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (data) 
    {
        stbi_image_free(data);
    }
    
    array_push(TexturesCollection, texture.RendererID);

    return texture;
}

void
graphics_texture2d_bind(Texture2D* texture, u32 slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture->RendererID);
}

void
graphics_texture2d_unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}