workspace "Moss"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"   
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sandbox"

    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
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
        systemversion "10.0.17763.0"

        defines
        {
            "MOSS_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "MO_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "MO_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "MO_DIST"
        symbols "On"


    
project "Moss"

    location "Moss"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.17763.0"

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
        symbols "On"

    filter "configurations:Release"
        defines "MO_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "MO_DIST"
        symbols "On"

