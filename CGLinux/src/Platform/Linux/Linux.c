#include "Linux.h"

#include <sys/resource.h>
#include "Utils/Logger.h"

void linux_set_application_stack(i64 currentBytesNumber, i64 maxBytesNumber)
{
    struct rlimit resource_limit;
	int result = getrlimit(RLIMIT_STACK, &resource_limit);
	if (result < 0)
	{
		GLOG(RED("get r limit error!\n"));
	}
	else 
	{
		GLOG("Resource limit: %lld\n", (i64)resource_limit.rlim_cur, (i64)resource_limit.rlim_max);
		resource_limit.rlim_cur = (i64) currentBytesNumber;
		resource_limit.rlim_max = (i64) maxBytesNumber;
		result = setrlimit(RLIMIT_STACK, &resource_limit);
		if (result == 0) 
		{
			GLOG(YELLOW("NEW") "Resource limit: %lld mb\n", 
			(i64)TOMB(resource_limit.rlim_cur), (i64)resource_limit.rlim_max);
		}
	}
}