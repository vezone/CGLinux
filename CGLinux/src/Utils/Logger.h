#pragma once

#include <stdio.h>

//GLBOBAL
#define DEBUG_MODE 0

#if DEBUG_MODE == 0
#define ISGLOBALLOG 1
#define ISGLOBALERROR 1
#define ISGLOBALWARNING 1
#define ISGLOBALDEBUG 1
#else
#define ISGLOBALLOG 0
#define ISGLOBALERROR 0
#define ISGLOBALWARNING 0
#define ISGLOBALDEBUG 0
#endif

#define ISFORMATTOSTRING 1

//Shader
#define ISSHADERDEBUG 0
//Buffers
#define ISBUFFERDEBUG 0

#if ISGLOBALLOG == 1
#define GLOG(format, ...) printf("[LOG] file: %s, line: %d, message: ", __FILE__, __LINE__);printf(format, ##__VA_ARGS__)
#else
#define GLOG(format, ...)
#endif

#if ISGLOBALERROR == 1
#define GERROR(format, ...) printf(RED("[ERROR]")" file: %s, line: %d, message: ", __FILE__, __LINE__);printf(format, ##__VA_ARGS__)
#else
#define GERROR(format, ...)
#endif

#if ISGLOBALWARNING == 1
#define GWARNING(format, ...) printf(YELLOW("[WARNING]")" file: %s, line: %d, message: ", __FILE__, __LINE__);printf(format, ##__VA_ARGS__)
#else
#define GWARNING(format, ...)
#endif

#if ISGLOBALDEBUG == 1
#define GDEBUG(format, ...) printf("[DEBUG] file: %s, line: %d, message: ", __FILE__, __LINE__);printf(format, ##__VA_ARGS__)
#define GLDEBUG(format, file, line, ...) printf(GREEN("[GL-DEBUG]")" file: %s, line: %d, message: ", file, line);printf(format, ##__VA_ARGS__)
#else
#define GDEBUG(format, ...)
#define GLDEBUG(format, file, line, ...)
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

#if ISBUFFERDEBUG == 1
#define BUFFERDEBUG(format, ...) GLOG(format, ##__VA_ARGS__)
#else
#define BUFFERDEBUG(format, ...)
#endif

