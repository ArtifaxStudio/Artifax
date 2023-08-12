workspace "Artifax"
    architecture "x64"
	startproject "Sandbox"

    configurations
    { 
        "Debug", 
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir)
-- struct(lua table) of includes
IncludeDir = {}
IncludeDir["spdlog"] = "Artifax/vendor/spdlog/include"
IncludeDir["GLFW"] = "Artifax/vendor/GLFW/include"
IncludeDir["Glad"] = "Artifax/vendor/Glad/include"
IncludeDir["ImGui"] = "Artifax/vendor/imgui"
IncludeDir["glm"] = "Artifax/vendor/glm"

-- Include GLFW premake.lua here (kind a copy)
include "Artifax/vendor/spdlog"
include "Artifax/vendor/GLFW"
include "Artifax/vendor/Glad"
include "Artifax/vendor/imgui"
include "Artifax/vendor/glm"

project "Artifax"
    location "Artifax"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "axpch.h"
    pchsource "Artifax/src/axpch.cpp"

    files 
    { 
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines 
        { 
            "AX_PLATFORM_WINDOWS",
            "AX_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "AX_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AX_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AX_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Artifax/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Artifax"
    }

    filter "system:windows"
        systemversion "latest"

	defines 
	{ 
		"AX_PLATFORM_WINDOWS"
	}

    filter "configurations:Debug"
        defines "AX_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AX_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AX_DIST"
        runtime "Release"
        optimize "on"