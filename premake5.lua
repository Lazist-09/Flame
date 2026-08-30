workspace "Flame"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory), add GLFW constract to this list
IncludeDirs = {}
IncludeDirs["GLFW"] = "Flame/vendor/GLFW/include"
IncludeDirs["Glad"] = "Flame/vendor/Glad/include"
IncludeDirs["ImGui"] = "Flame/vendor/Imgui"
IncludeDirs["glm"] = "Flame/vendor/glm"

include "Flame/vendor/GLFW"
include "Flame/vendor/Glad"
include "Flame/vendor/Imgui"

project "Flame"
	location "Flame"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir.."/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "flpch.h"
	pchsource "Flame/src/flpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		-- GLM 是头文件库，将头文件加入解决方案便于浏览
		"%{prj.name}/vendor/glm/glm/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.Glad}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.glm}"

	}
	
	links{
		"GLFW",
		"opengl32.lib",
		"Glad",
		"ImGui"
	}



	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"
		buildoptions "/utf-8"

		defines
		{
			"FL_PLATFORM_WINDOWS",
			"FLAME_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "FL_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "FL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FL_DIST"
		runtime "Release"
		optimize "On"
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir.."/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Flame/vendor/spdlog/include",
		"Flame/src",
		"%{IncludeDirs.glm}"
	}

	links
	{
		"Flame"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"
		buildoptions "/utf-8"

		defines
		{
			"FL_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "FL_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "FL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FL_DIST"
		runtime "Release"
		optimize "On"