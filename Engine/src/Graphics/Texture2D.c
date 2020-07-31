#include "Texture2D.h"

#include <glad/glad.h>

#include "OpenGLBase.h"
#include "Utils/Array.h"
#include "Utils/stb_image.h"
#include "Utils/Logger.h"

u32* TexturesCollection = NULL;

Texture2D 
graphics_texture2d_create(const char* path)
{
    i32 width, height, channels;
    GLenum dataFormat, internalFormat;
    Texture2D texture = {
        .Path = path
    };
    TEXTUREDEBUG("Texture path: %s\n", path);

    //Enable blending
    GLCheck(glEnable(GL_BLEND));
    GLCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(path, 
        &width, &height, &channels, 0);
    if (!data) 
    {
        GERROR("Failed to load a texture!");
    }

    texture.Width = width;
    texture.Height = height;
    texture.Channels = channels;

    TEXTUREDEBUG("Channels: %d\n", channels);

    if (channels == 3) 
    {
        dataFormat = GL_RGB;
        internalFormat = GL_RGB8;
    }
    else if (channels == 4) 
    {
        dataFormat = GL_RGBA;
        internalFormat = GL_RGBA8;
    }

    GLCheck(glCreateTextures(GL_TEXTURE_2D, 1, &texture.RendererID));
    GLCheck(glTextureStorage2D(texture.RendererID, 1, internalFormat,
        texture.Width, texture.Height));
    
    GLCheck(glTextureParameteri(texture.RendererID, 
        GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCheck(glTextureParameteri(texture.RendererID, 
        GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCheck(glTextureParameteri(texture.RendererID, 
        GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCheck(glTextureParameteri(texture.RendererID, 
        GL_TEXTURE_WRAP_T, GL_REPEAT));

    GLCheck(glTextureSubImage2D(texture.RendererID, 0, 0, 0, 
        texture.Width, texture.Height,
        dataFormat, GL_UNSIGNED_BYTE, data));

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
    texture->Slot = slot;
    GLCheck(glBindTextureUnit(slot, texture->RendererID));
}

void
graphics_texture2d_unbind(Texture2D* texture)
{
    GLCheck(glBindTextureUnit(texture->Slot, 0));
}

void
graphics_texture2d_delete(Texture2D* texture)
{
    GLCheck(glDeleteTextures(1, &texture->RendererID));
}
