#ifndef OPENGLBASE
#define OPENGLBASE

#define GLCheck(x) (x)

#include <glad/glad.h>
#include "Utils/Logger.h"

int opengl_context_init(void (*gladLoadProc)(const char* procnName));
void opengl_error_callback(GLenum source, GLenum error, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);


#endif
