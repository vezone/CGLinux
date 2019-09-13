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

group "Dependencies"
	include "Dependencies/GLFW"
	include "Dependencies/glad"

project "CGLinux"
	location "CGLinux"
	kind "ConsoleApp"
	language "C"

	buildoptions { "-std=c99" }
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/Intermidiates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/vlib/core/**.h",
		"%{prj.name}/src/vlib/core/**.c",
		"%{prj.name}/src/graphics/**.h",
		"%{prj.name}/src/graphics/**.c"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLAD}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"GL", "GLU", "X11",
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
