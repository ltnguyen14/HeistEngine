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
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hspch.h"
	pchsource "HeistEngine/src/hspch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	libdirs {
		"%{prj.name}/deps/GLFW/lib-vc2019"
	}

	links {
		"opengl32.lib",
		"glfw3dll",
	}

	includedirs {
		"%{prj.name}/deps/spdlog/include",
		"%{prj.name}/deps/GLFW/include",
		"%{prj.name}/src",
		"%{prj.name}/src/HeistEngine",
		"%{prj.name}/src/HeistEngine/Platform"
	}

	filter "system:windows"
		systemversion "10.0.17763.0"

		defines {
			"HEIST_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} deps/GLFW/lib-vc2019 ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines {
			"HS_DEBUG",
			"HS_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines {
			"HS_RELEASE"
		}
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines {
			"HS_DIST"
		}
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"HeistEngine/deps/GLFW/include",
		"HeistEngine/deps/spdlog/include",
		"HeistEngine/src",
		"HeistEngine/src/HeistEngine",
	}

	links {
		"HeistEngine",
	}

	filter "system:windows"
		systemversion "10.0.17763.0"

		defines {
			"HEIST_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines {
			"HS_DEBUG",
			"HS_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines {
			"HS_RELEASE"
		}
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines {
			"HS_DIST"
		}
		runtime "Release"
		optimize "On"