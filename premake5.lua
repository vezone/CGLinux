workspace "Engine"
architecture "x64"
startproject "Sandbox"

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

group "Dependencies"
include "Dependencies/GLFW"
include "Dependencies/glad"

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C"
    staticruntime "on"

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
      "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
      "%{prj.name}/src",
      "%{IncludeDirs.GLFW}",
      "%{IncludeDirs.GLAD}",
      "%{IncludeDirs.CGLM}"
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
    defines "ENGINE_DEBUG = 1"
    symbols "On"

    filter "configurations:Release"
    defines "ENGINE_DEBUG = 0"
    optimize "On"

    filter "configurations:Dist"
    defines "ENGINE_DIST"
    optimize "On"

project "SandboxApp"
    location "SandboxApp"
    kind "ConsoleApp"
    language "C"
    staticruntime "on"

    buildoptions
    {
      "-std=c99",
      "-O3"
    }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/Intermidiates/" .. outputdir .. "/%{prj.name}")

    files
    {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.c"
    }

    defines
    {
      "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
      "Engine/src",
      "Dependencies",
      "%{IncludeDirs.GLFW}",
      "%{IncludeDirs.GLAD}",
      "%{IncludeDirs.CGLM}"
    }

    links
    {
      "Engine",
      "glad",
      "GLFW",
      "stdc++",
      "GL", "GLU",
      "X11","dl",
      "Xinerama", "Xcursor", "m",
      "Xxf86vm", "Xrandr", "pthread", "Xi"
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
