#include "App/Sandbox.h"
#include "Utils/stb_ds.h"
#include "Utils/Types.h"
#include "Utils/Logger.h"

/*
  TODO:
  big refactoring in renderer

  TODO:
	* create renderer2d_submit(), renderer2d_flush()
	* create transformation (model matrix)
	* create resizing
	* create MVP
	* create application
	* create linux file with platform dependent code
	* create _

	IDEA:
	* we can create static lib (.a) for game code and load it by toolkit dynamicly [we can use dlopen(LoadLibrary) dlclose(FreeLibrary) dlsym(GetProcAddress) function, here is link: https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dlopen.3.html] 
	
*/

typedef struct Type {
	const char* key;
	u32 value;
} Type;

int main()
{
	sandbox_start();

#if 0
	Type *hash = NULL;

	const char* uniform_1 = "Transform";
	const char* uniform_2 = "Size";
	const char* uniform_3 = "Position_z";
	const char* uniform_4 = "Light";
	const char* uniform_5 = "Blabla";
	const char* uniform_6 = "BlumBlum";

	shput(hash, uniform_1, 11);
	shput(hash, uniform_2, 22);
	shput(hash, uniform_3, 33);
	shput(hash, uniform_4, 44);
	shput(hash, uniform_5, 55);
	shput(hash, uniform_6, 66);
	
	u32 v1 = shget(hash, uniform_1);
	u32 v2 = shget(hash, uniform_2);
	u32 v3 = shget(hash, uniform_3);
	u32 v4 = shget(hash, uniform_4);
	u32 v5 = shget(hash, uniform_5);
	u32 v6 = shget(hash, uniform_6);

	GLOG("v1 = %d\nv2 = %d\nv3 = %d\nv4 = %d\nv5 = %d\nv6 = %d\n", v1,v2,v3,v4,v5,v6);

	i32 result = shgeti(hash, "key");
	GLOG("result: %d\n", result);
	
	shfree(hash);
#endif
	
	return 0;
}
