workspace "CGLinux"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs
IncludeDirs = {}
IncludeDirs["GLFW"] = "Dependencies/GLFW/include" 
IncludeDirs["GLAD"] = "Dependencies/glad/include" 
IncludeDirs["CGLM"] = "Dependencies/CGLM/include" 
IncludeDirs["CIMGUI"] = "Dependencies/CImGUI"

group "Dependencies"
	include "Dependencies/GLFW"
	include "Dependencies/glad"
	include "Dependencies/CImGUI"

project "CGLinux"
	location "CGLinux"
	kind "ConsoleApp"
	language "C"

	buildoptions { "-std=c99", "-O3" }
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/Intermidiates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"CIMGUI_DEFINE_ENUMS_AND_STRUCTS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.CGLM}",
		"%{IncludeDirs.CIMGUI}"
	}

	links
	{
		"GLAD",
		"GLFW",
		"CImGUI",
		"stdc++",
		"GL", "GLU",
		"X11","dl",
		"Xinerama", "Xcursor", "m",
		"Xxf86vm", "Xrandr", "pthread", "Xi"
	}

	filter "system:linux"
	       defines
	       {
	           LINUX_PLATFORM
	       }

	filter "system:windows"
		defines
		{
		    WINDOWS_PLATFORM
		}

	filter "configurations:Debug"
		defines "CG_DEBUG = 1"
		symbols "On"

	filter "configurations:Release"
		defines "CG_DEBUG = 0"
		optimize "On"

	filter "configurations:Dist"
		defines "CG_DIST"
		optimize "On"
