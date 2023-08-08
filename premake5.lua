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
IncludeDir["GLFW"] = "Artifax/vendor/GLFW/include"
IncludeDir["Glad"] = "Artifax/vendor/Glad/include"
IncludeDir["ImGui"] = "Artifax/vendor/imgui"

-- Include GLFW premake.lua here (kind a copy)
include "Artifax/vendor/GLFW"
include "Artifax/vendor/Glad"
include "Artifax/vendor/imgui"

project "Artifax"
    location "Artifax"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "axpch.h"
    pchsource "Artifax/src/axpch.cpp"

    files 
    { 
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        { 
            "AX_PLATFORM_WINDOWS",
            "AX_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
			("{MKDIR} %{wks.location}/bin/" .. outputdir .. "/Sandbox"),
            ("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/Artifax.dll")
        }

    filter "configurations:Debug"
        defines "AX_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "AX_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "AX_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Artifax/vendor/spdlog/include",
        "Artifax/src"
    }

    links
    {
        "Artifax"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

	defines 
	{ 
		"AX_PLATFORM_WINDOWS"
	}

    filter "configurations:Debug"
        defines "AX_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "AX_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "AX_DIST"
        buildoptions "/MD"
        optimize "On"