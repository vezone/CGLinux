#include "FrameBuffer.h"
#include <glad/glad.h>
#include <assert.h>
#include <stdlib.h>
#include "Utils/Logger.h"

void framebuffer_invalidate(FrameBuffer* framebuffer, u32 width, u32 height, u32 samples)
{
    glCreateFramebuffers(1, &framebuffer->RendererId);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->RendererId);

    //GL_RGBA -> GL_RGB
    glCreateTextures(GL_TEXTURE_2D, 1, &framebuffer->ColorAttachment);
    glBindTexture(GL_TEXTURE_2D, framebuffer->ColorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer->ColorAttachment, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &framebuffer->DepthAttachment);
    glBindTexture(GL_TEXTURE_2D, framebuffer->DepthAttachment);
    //glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, framebuffer->DepthAttachment, 0);

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    framebuffer->Width = width;
    framebuffer->Height = height;
}

void framebuffer_bind(FrameBuffer* framebuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->RendererId);
}

void framebuffer_unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void framebuffer_destroy(FrameBuffer* framebuffer)
{
    glDeleteFramebuffers(1, &framebuffer->RendererId);
}

u8* data = NULL;
void* framebuffer_get_image(FrameBuffer* framebuffer)
{
#if 1
    i32 size = 3 * framebuffer->Width * framebuffer->Height;
    GLOG("Before\n");
    if (data == NULL)
    {
	data = malloc(size);
	glReadPixels(0, 0, framebuffer->Width, framebuffer->Height, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    GLOG("After: %c\n", data[0]);
    //glGetTextureImage(framebuffer->ColorAttachment, 0, GL_RGBA8, GL_UNSIGNED_BYTE, size, data);

    //glReadPixels(0, 0, framebuffer->Width, framebuffer->Height, GL_RGB, GL_UNSIGNED_BYTE, data);

    return data;
#endif
}

void framebuffer_get_current_image()
{
}
