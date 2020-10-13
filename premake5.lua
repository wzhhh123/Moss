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

include "Moss/vendor/GLFW"  --����c++��ͷ�ļ����ã�����glfw�����premake5�ļ�
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
		"GLFW",   --include��glfw��premake5�������и�project��GLFW
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
		runtime "Debug"   --�����п���MDd ���̵߳���dll
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
        --buildoptions "/MDd"     --multi thread dll �ڴ�������-���п�����  MDd�Ƕ��̵߳���dll����������crash���²��������debug��ʹ��release��spdlog��spdlog��ĳЩ�ڴ���release�»����٣�debug�³��Ի�ȡ��ʱ��Ƿ��ˣ�Ҫ��spd�ĳ�debug
        symbols "On"
    
    filter "configurations:Release"
        defines "MS_RELEASE"
        runtime "Release"
        symbols "On"

    filter "configurations:Dist"
        defines "MS_DIST"
        runtime "Release"
        symbols "On"


    
