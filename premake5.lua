workspace "Moss"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"   
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Moss/vendor/GLFW/include"
IncludeDir["GLAD"] = "Moss/vendor/GLAD/include"

include "Moss/vendor/GLFW"  --类似c++的头文件引用，引用glfw下面的premake5文件
include "Moss/vendor/GLAD" 

project "Moss"

    location "Moss"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "mspch.h"
	pchsource "Moss/src/mspch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/Platform/**.h",
        "%{prj.name}/Platform/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
    }

	links
	{
		"GLFW",   --include了glfw的premake5，里面有个project叫GLFW
		"opengl32.lib",
		"GLAD"
	}

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "MOSS_PLATFORM_WINDOWS",
            "MOSS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "MO_DEBUG"
		buildoptions "/MDd"     --multi thread dll 在代码生成-运行库下面  MDd是多线程调试dll，貌似这样看到dll的堆栈
        symbols "On"

    filter "configurations:Release"
        defines "MO_RELEASE"
		buildoptions "/MD"
        symbols "On"

    filter "configurations:Dist"
        defines "MO_DIST"
		buildoptions "/MD"
        symbols "On"



project "Sandbox"

    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "Moss/src"
    }

    links
    {
        "Moss"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "MOSS_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "MO_DEBUG"
        buildoptions "/MDd"     --multi thread dll 在代码生成-运行库下面  MDd是多线程调试dll，不这样会crash，猜测是如果在debug下使用release的spdlog，spdlog的某些内存在release下会销毁，debug下尝试获取的时候非法了，要把spd改成debug
        symbols "On"
    
    filter "configurations:Release"
        defines "MO_RELEASE"
        buildoptions "/MD"
        symbols "On"

    filter "configurations:Dist"
        defines "MO_DIST"
        buildoptions "/MD"
        symbols "On"


    
