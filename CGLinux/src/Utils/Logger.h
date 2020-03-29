#pragma once

#include <stdio.h>
#include "Types.h"

#define ISGLOBALLOG 1
#define ISGLOBALDEBUG 0
#define ISFORMATTOSTRING 1

#if ISGLOBALLOG == 1
#define GLOG(format, ...) printf("file: %s, line: %d, message: ", __FILE__, __LINE__);printf(format, ##__VA_ARGS__)
#else
#define GLOG(format, ...)
#endif

#define GERROR(format, ...) GLOG(RED(format), ##__VA_ARGS__) 

#if ISGLOBALDEBUG == 1
	#define GDEBUG(format, ...) printf("file: %s, line: %d, message: ", __FILE__, __LINE__);printf(format, ##__VA_ARGS__)
#else
	#define GDEBUG(format, ...)
#endif

#if ISFORMATTOSTRING == 1
	#define GFORMAT(string, format, ...) sprintf(string, format, __VA_ARGS__)
#else
	#define GFORMAT(string, format, ...)
#endif

