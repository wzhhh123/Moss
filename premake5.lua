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
IncludeDir["stb_image"] = "Moss/vendor/stb_image"

include "Moss/vendor/GLFW"  --����c++��ͷ�ļ����ã�����glfw�����premake5�ļ�
include "Moss/vendor/GLAD" 
include "Moss/vendor/imgui"


project "Moss"

    location "Moss"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"  --ʹ��sharedLib��ʱ��Ҫ�رգ�ʲôStaticLib�ڴ���䷽ʽ�Ƕ�̬�ģ�ÿ�ι����ڴ�λ�ö���һ����debug��ȷ����release��ʱ���crash������Ҫ�ö�̬�ģ��رվ�̬runtime??

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
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
    }

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	links
	{
		"GLFW",   --include��glfw��premake5�������и�project��GLFW
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
			runtime "Debug"   --�����п���MDd ���̵߳���dll
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


    
