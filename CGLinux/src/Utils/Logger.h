#pragma once

#include <stdio.h>

#define ISGLOBALLOG 1
#define ISGLOBALDEBUG 1

#if ISGLOBALLOG == 1
	#define GLOG(...) printf(__VA_ARGS__)
#else
	#define GLOG(...)
#endif

#if ISGLOBALDEBUG == 1
	#define GDEBUG(...) printf(__VA_ARGS__)
#else
	#define GDEBUG(...)
#endif

