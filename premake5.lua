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
    kind "SharedLib"
    language "C++"
	staticruntime "off"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "mspch.h"
	pchsource "Moss/src/mspch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/Platform/**.h",
        "%{prj.name}/Platform/**.cpp",
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

	links
	{
		"GLFW",   --include了glfw的premake5，里面有个project叫GLFW
		"opengl32.lib",
		"GLAD",
		"ImGui",
	}

    filter "system:windows"
        cppdialect "C++17"
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
        symbols "On"

    filter "configurations:Release"
        defines "MS_RELEASE"
	    runtime "Release"
        symbols "On"

    filter "configurations:Dist"
        defines "MS_DIST"
        runtime "Release"
        symbols "On"



project "Sandbox"

    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
	staticruntime "off"

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
		"%{IncludeDir.glm}",
    }

    links
    {
        "Moss"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "MOSS_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "MS_DEBUG"
		runtime "Debug"
        --buildoptions "/MDd"     --multi thread dll 在代码生成-运行库下面  MDd是多线程调试dll，不这样会crash，猜测是如果在debug下使用release的spdlog，spdlog的某些内存在release下会销毁，debug下尝试获取的时候非法了，要把spd改成debug
        symbols "On"
    
    filter "configurations:Release"
        defines "MS_RELEASE"
        runtime "Release"
        symbols "On"

    filter "configurations:Dist"
        defines "MS_DIST"
        runtime "Release"
        symbols "On"


    
