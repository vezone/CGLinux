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

int main()
{
    i32 returnCode;
    returnCode = sandbox_start();
	
	return returnCode;
}
