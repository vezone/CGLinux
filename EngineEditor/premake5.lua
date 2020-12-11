outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "EngineEditor"
    location "EngineEditor"
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
      "GLFW_INCLUDE_NONE",
      "CIMGUI_DEFINE_ENUMS_AND_STRUCTS"
    }

    includedirs
    {
      "Engine/src",
      "%{IncludeDirs.GLFW}",
      "%{IncludeDirs.GLAD}",
      "Dependencies",
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
      "Xxf86vm", "Xrandr", "pthread", "Xi",
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
