workspace "HeistEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "HeistEngine"
	location "HeistEngine"
	kind "sharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hspch.h"
	pchsource "HeistEngine/src/hspch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/deps/spdlog/include",
		"%{prj.name}/src",
		"%{prj.name}/src/HeistEngine",
		"%{prj.name}/src/HeistEngine/Platform"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"

		defines {
			"HEIST_PLATFORM_WINDOWS",
			"HEIST_BUILD_DLL",
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines {
			"HS_DEBUG",
			"HS_ENABLE_ASSERTS"
		}
		symbols "On"

	filter "configurations:Release"
		defines {
			"HS_RELEASE"
		}
		optimize "On"

	filter "configurations:Dist"
		defines {
			"HS_DIST"
		}
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"HeistEngine/deps/spdlog/include",
		"HeistEngine/src"
	}

	links {
		"HeistEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"

		defines {
			"HEIST_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines {
			"HS_DEBUG",
			"HS_ENABLE_ASSERTS"
		}
		symbols "On"

	filter "configurations:Release"
		defines {
			"HS_RELEASE"
		}
		optimize "On"

	filter "configurations:Dist"
		defines {
			"HS_DIST"
		}
		optimize "On"