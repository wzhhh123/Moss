workspace "Moss"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"   
    }
    
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Moss/vendor/GLFW/include"
IncludeDir["GLAD"] = "Moss/vendor/GLAD/include"
IncludeDir["imgui"] = "Moss/vendor/imgui"
IncludeDir["glm"] = "Moss/vendor/glm"

include "Moss/vendor/GLFW"  --类似c++的头文件引用，引用glfw下面的premake5文件
include "Moss/vendor/GLAD" 
include "Moss/vendor/imgui"


project "Moss"

    location "Moss"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"  --使用sharedLib的时候要关闭，什么StaticLib内存分配方式是动态的，每次构建内存位置都不一样，debug正确，在release的时候会crash，所以要用动态的，关闭静态runtime??

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "mspch.h"
	pchsource "Moss/src/mspch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
    }

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	links
	{
		"GLFW",   --include了glfw的premake5，里面有个project叫GLFW
		"opengl32.lib",
		"GLAD",
		"ImGui",
	}

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "MOSS_PLATFORM_WINDOWS",
            "MOSS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
        }
	
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

		filter "configurations:Debug"
			defines "MS_DEBUG"
			runtime "Debug"   --让运行库变成MDd 多线程调试dll
			symbols "on"  --generate debug symbols

		filter "configurations:Release"
			defines "MS_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "MS_DIST"
			runtime "Release"
			optimize "on"



project "Sandbox"

    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Moss/vendor/spdlog/include",
        "Moss/src",
		"Moss/vendor",
		"%{IncludeDir.glm}",
    }

    links
    {
        "Moss"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "MOSS_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "MS_DEBUG"
		runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "MS_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "MS_DIST"
        runtime "Release"
        optimize "on"


    
