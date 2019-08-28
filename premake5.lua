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

group "Dependencies"
	include "Dependencies/GLFW"

project "CGLinux"
	location "CGLinux"
	kind "ConsoleApp"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/Intermidiates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/vlib/core/**.h",
		"%{prj.name}/src/vlib/core/**.c",
		"%{prj.name}/src/vlib/graphics/**.h",
		"%{prj.name}/src/vlib/graphics/**.c"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDirs.GLFW}"
	}

	links
	{
		"GLFW",
		"GL", "GLU", "glfw3", "X11",
		"dl", "Xinerama", "Xcursor", "m",
		"Xxf86vm", "Xrandr", "pthread", "Xi"
	}

	filter "configurations:Debug"
		defines "CG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CG_DIST"
		optimize "On"
