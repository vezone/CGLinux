#pragma once

#include <stdio.h>
#include "Types.h"

//GLBOBAL
#define ISGLOBALLOG 1
#define ISGLOBALDEBUG 1
#define ISFORMATTOSTRING 1
//Shader
#define ISSHADERDEBUG 0
#define ISSHADERLOG 0
//Buffers
#define ISBUFFERDEBUG 0
#define ISBUFFERLOG 0

#if ISGLOBALLOG == 1
#define GLOG(format, ...) printf("[LOG] file: %s, line: %d, message: ", __FILE__, __LINE__);printf(format, ##__VA_ARGS__)
#else
#define GLOG(format, ...)
#endif

#define GERROR(format, ...) GLOG(RED(format), ##__VA_ARGS__) 

#if ISGLOBALDEBUG == 1
#define GDEBUG(format, ...) printf("[DEBUG] file: %s, line: %d, message: ", __FILE__, __LINE__);printf(format, ##__VA_ARGS__)
#else
#define GDEBUG(format, ...)
#endif
#define GPRINTI32(var) const char* format = #var;\
  GLOG(#var": %d\n", var)

#if ISFORMATTOSTRING == 1
#define GFORMAT(string, format, ...) sprintf(string, format, __VA_ARGS__)
#else
#define GFORMAT(string, format, ...)
#endif


#if ISSHADERDEBUG == 1
#define SHADERDEBUG(format, ...) GLOG(format, ##__VA_ARGS__)
#else
#define SHADERDEBUG(format, ...)
#endif

#if ISSHADERLOG == 1
#define SHADERLOG(format, ...) GLOG(format, ##__VA_ARGS__)
#else
#define SHADERLOG(format, ...)
#endif

#if ISBUFFERDEBUG == 1
#define BUFFERDEBUG(format, ...) GLOG(format, ##__VA_ARGS__)
#else
#define BUFFERDEBUG(format, ...)
#endif

#if ISBUFFERLOG == 1
#define BUFFERLOG(format, ...) GLOG(format, ##__VA_ARGS__)
#else
#define BUFFERLOG(format, ...)
#endif
