#include "OpenGLBase.h"
#include "Utils/Logger.h"
#include "Utils/Types.h"

void
opengl_get_error(const char* file, const char* line)
{
  i32 error;
  while ((error = glGetError()) != GL_NO_ERROR)
  {
	switch (error)
	  {
	  case GL_NO_ERROR:
		{
		  break;
		}
	  case GL_INVALID_ENUM:
		{
		  GLDEBUG("GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.\n", file, line);
		  break;  
		}
	  case GL_INVALID_VALUE:
		{
		  GLDEBUG("GL_INVALID_VALUE: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.\n", file, line);
		  break;  
		}
	  case GL_INVALID_OPERATION:
		{
		  GLDEBUG("GL_INVALID_OPERATION: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.\n", file, line);
		  break;  
		}
	  case GL_INVALID_FRAMEBUFFER_OPERATION:
		{
		  GLDEBUG("GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.\n", file, line);
		  break;  
		}
	  case GL_OUT_OF_MEMORY:
		{
		  GLDEBUG("GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.\n", file, line);
		  break;  
		}
	  case GL_STACK_UNDERFLOW:
		{
		  GLDEBUG("GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.\n", file, line);
		  break;  
		}
	  case GL_STACK_OVERFLOW:
		{
		  GLDEBUG("GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.\n", file, line);
		  break;  
		}
	  default:
		{
		  GLDEBUG("Unknown error\n", file, line);
		  break;
		}
	  }	  
  }
}
