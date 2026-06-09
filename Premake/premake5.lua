IncludeDir = {}
IncludeDir["GLFW"]    = "%{wks.location}/Hane/vendor/GLFW/include"
IncludeDir["include"] = "%{wks.location}/Hane/vendor/include"
IncludeDir["imgui"]   = "%{wks.location}/Hane/vendor/include/imgui"
IncludeDir["glad"]    = "%{wks.location}/Hane/vendor/include"
IncludeDir["KHR"]     = "%{wks.location}/Hane/vendor/include/KHR"
IncludeDir["stb"]     = "%{wks.location}/Hane/vendor/include/stb"
IncludeDir["glm"]     = "%{wks.location}/Hane/vendor/include/glm"

LibraryDir = {}
LibraryDir["glfw3"] = "%{wks.location}/Hane/vendor/GLFW/bin/%{cfg.architecture}/%{cfg.buildcfg}"

Library = {}
Library["glfw3"] = "%{LibraryDir.glfw3}/glfw3_Debug.lib" -- ako je imamo u nasem solutionu onda dodajemo ovde,  u suprotnom kao sto je opengl32 onda samo navedemo u links

----------------------------------------------------------------------------------------

workspace "Hane"
	location "../"
	architecture "x64" 
	startproject "Hane"

	configurations
	{
		"Debug",
		"Release"
	}

-- outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
outputdir = "%{cfg.architecture}-%{cfg.buildcfg}"

group "Core"
	project "Hane"
group ""

group "Dependencies"
	project "GLFW"
group ""

group "Tools"
--	include "Premake5"
group ""

----------------
--    Hane    --
----------------

project "Hane"
	location "../Hane" -- nalazi se u Hane folder relativno na ovaj fajl
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.location}/*.h",
		"%{prj.location}/*.cpp",

		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp",

		"%{prj.location}/vendor/include/stb/**.h",
		"%{prj.location}/vendor/include/stb/**.cpp",

		"%{prj.location}/vendor/include/glm/glm/**.hpp",
		"%{prj.location}/vendor/include/glm/**.inl",

		"%{prj.location}/vendor/include/KHR/**.h",

		"%{prj.location}/vendor/include/imgui/**.h",
		"%{prj.location}/vendor/include/imgui/**.cpp",

		"%{prj.location}/vendor/include/glad/**.h",
		"%{prj.location}/vendor/include/glad/**.c",
	}

	--excludefrombuild {"%{prj.location}/vendor/include/imgui/backends/imgui_impl_glut.cpp"}

	defines{
		"_CRT_SECURE_NO_WARNINGS",
	}

	includedirs{
		"src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.KHR}",
	}

	libdirs{
		"%{prj.location}/vendor/GLFW/bin/%{cfg.architecture}/%{cfg.buildcfg}"
	}


	removefiles{
		"%{prj.location}/vendor/include/imgui/backends/imgui_impl_glut.cpp"
	}

	links {
		"GLFW",         -- oznacavamo da Hane zavisi od GLFW tako da se prvo builda GLFW
		"opengl32",
		"glfw3_Debug"
	}

	filter "configurations:Debug"
		runtime "Debug"
		targetname "Hane_Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		targetname "Hane_Release"
		optimize "on"

	filter "system:windows"
		systemversion "latest" -- Windows SDK Version

----------------
--    GLFW    --
----------------

project "GLFW"
	location "../Hane/vendor/GLFW"
	kind "StaticLib"
	language "C"
	staticruntime "On" -- Sets <RuntimeLibrary> to "MultiThreaded" -- Sets at command line "/MT" for Release and "/MTd" for Debug

	targetdir ("%{prj.location}/bin/%{cfg.architecture}/%{cfg.buildcfg}"    )
	objdir (   "%{prj.location}/bin-int/%{cfg.architecture}/%{cfg.buildcfg}")

	files
	{
		"%{prj.location}/include/GLFW/glfw3.h",
		"%{prj.location}/include/GLFW/glfw3native.h",

		"%{prj.location}/src/glfw_config.h",
		"%{prj.location}/src/context.c",
		"%{prj.location}/src/init.c",
		"%{prj.location}/src/input.c",
		"%{prj.location}/src/monitor.c",
		"%{prj.location}/src/vulkan.c",
		"%{prj.location}/src/window.c",
		"%{prj.location}/src/*.c"
	}

	defines 
	{ 
		"_GLFW_WIN32",
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "configurations:Debug"
		runtime "Debug"
		targetname "glfw3_Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		targetname "glfw3_Release"
		optimize "on"

	filter "system:windows"
		systemversion "latest" -- Windows SDK Version
