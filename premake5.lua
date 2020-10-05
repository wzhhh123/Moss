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

include "Moss/vendor/GLFW"  --����c++��ͷ�ļ����ã�����glfw�����premake5�ļ�

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
		"%{IncludeDir.GLFW}"
    }

	links
	{
		"GLFW",   --include��glfw��premake5�������и�project��GLFW
		"opengl32.lib"
	}

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "MOSS_PLATFORM_WINDOWS",
            "MOSS_BUILD_DLL",
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "MO_DEBUG"
		buildoptions "/MDd"     --multi thread dll �ڴ�������-���п�����  MDd�Ƕ��̵߳���dll��ò����������dll�Ķ�ջ
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
        buildoptions "/MDd"     --multi thread dll �ڴ�������-���п�����  MDd�Ƕ��̵߳���dll����������crash���²��������debug��ʹ��release��spdlog��spdlog��ĳЩ�ڴ���release�»����٣�debug�³��Ի�ȡ��ʱ��Ƿ��ˣ�Ҫ��spd�ĳ�debug
        symbols "On"
    
    filter "configurations:Release"
        defines "MO_RELEASE"
        buildoptions "/MD"
        symbols "On"

    filter "configurations:Dist"
        defines "MO_DIST"
        buildoptions "/MD"
        symbols "On"


    
