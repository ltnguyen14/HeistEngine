workspace "HeistEngine"
architecture "x64"
startproject "Sandbox"

configurations {
  "Debug",
  "Release",
  "Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Glad"] = "HeistEngine/deps/GLAD/include"
IncludeDir["GLFW"] = "HeistEngine/deps/GLFW/include"

include "HeistEngine/deps/GLAD"
include "HeistEngine/deps/GLFW"

-- Heist Engine

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

links {
  "opengl32.lib",
  "GLFW",
  "Glad"
}

includedirs {
  "%{prj.name}/deps/spdlog/include",
  "%{prj.name}/src",
  "%{prj.name}/src/HeistEngine",
  "%{IncludeDir.Glad}",
  "%{IncludeDir.GLFW}"
}

filter "system:windows"
systemversion "latest"

defines {
  "HEIST_PLATFORM_WINDOWS",
  "RENDERER_OPENGL",
  "GLFW_INCLUDE_NONE"
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

-- Sandbox
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
