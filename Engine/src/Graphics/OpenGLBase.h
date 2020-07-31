#ifndef OPENGLBASE

#define OPENGLBASE
#include <glad/glad.h>

#if CG_DEBUG == 1
void opengl_get_error();
#define GLClearErrors() while (glGetError() != GL_NO_ERROR);
#define GLCheck(x) GLClearErrors(); x; opengl_get_error(__FILE__, __LINE__)
#else
#define GLCheck(x) x
#endif

#endif
