IncludeDir = {}
IncludeDir["GLFW"]          = "%{wks.location}/Hane/vendor/GLFW/include"
IncludeDir["imgui"]         = "%{wks.location}/Hane/vendor/include/imgui"

IncludeDir["glad"]          = "%{wks.location}/Hane/vendor/glad/include"
IncludeDir["KHR"]           = "%{wks.location}/Hane/vendor/KHR/include"

IncludeDir["stb_image"]     = "%{wks.location}/Hane/vendor/stb_image/include"

IncludeDir["glm"]           = "%{wks.location}/Hane/vendor/include"

-------------------------------------------------------------------------------------------

LibraryDir = {}
LibraryDir["glfw3"]     = "%{wks.location}/Hane/vendor/GLFW/bin/%{cfg.architecture}/%{cfg.buildcfg}"
LibraryDir["glad"]      = "%{wks.location}/Hane/vendor/glad/bin/%{cfg.architecture}/%{cfg.buildcfg}"
LibraryDir["stb_image"] = "%{wks.location}/Hane/vendor/stb_image/bin/%{cfg.architecture}/%{cfg.buildcfg}"
--LibraryDir["glm"]       = "%{wks.location}/Hane/vendor/glm/bin/%{cfg.architecture}/%{cfg.buildcfg}"

Library = {}
Library["glfw3"]     = "%{LibraryDir.glfw3}/glfw3.lib" -- ako je imamo u nasem solutionu onda dodajemo ovde,  u suprotnom kao sto je opengl32 onda samo navedemo u links
Library["glad"]      = "%{LibraryDir.glad}/glad.lib"
Library["stb_image"] = "%{LibraryDir.stb_image}/stb_image.lib"
--Library["glm"]       = "%{LibraryDir.glm}/glm.lib"

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

outputdir = "%{cfg.architecture}-%{cfg.buildcfg}"

group "Core"
	project "Hane"
group ""

group "Dependencies"
	project "GLFW"
	project "GLAD"
	project "stb_image"
	--project "glm"
group ""

group "Tools"
	project "premake5"
group ""

----------------
--    Hane    --
----------------

project "Hane"
	location "../Hane" -- nalazi se u Hane folder relativno na ovaj fajl
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files{ -- Which files to be included in project, filter VS

		"%{prj.location}/main.cpp", -- Hane files

		"%{prj.location}/src/**.h", -- Hane files
		"%{prj.location}/src/**.cpp", -- Hane files

		"%{prj.location}/vendor/include/glm/**.hpp",
		"%{prj.location}/vendor/include/glm/**.inl",

		"%{prj.location}/vendor/include/imgui/**.h",
		"%{prj.location}/vendor/include/imgui/**.cpp"
	}

	defines{
		"_CRT_SECURE_NO_WARNINGS",
	}

	includedirs{
		"%{IncludeDir.imgui}",
		"%{IncludeDir.GLFW}",

		"%{IncludeDir.glad}",
		"%{IncludeDir.KHR}",

		"%{IncludeDir.glm}",

		"%{IncludeDir.stb_image}",
	}

	libdirs{
		"%{prj.location}/vendor/GLFW/bin/%{cfg.architecture}/%{cfg.buildcfg}",
		"%{prj.location}/vendor/glad/bin/%{cfg.architecture}/%{cfg.buildcfg}",
		"%{prj.location}/vendor/stb_image/bin/%{cfg.architecture}/%{cfg.buildcfg}",
		--"%{prj.location}/vendor/glm/bin/%{cfg.architecture}/%{cfg.buildcfg}",
	}

	removefiles{
		"%{prj.location}/vendor/include/imgui/backends/imgui_impl_glut.cpp" -- Kako resiti ovo malo je weird da uklanjam samo jedan fajl
	}

	filter "configurations:Debug"
		runtime "Debug"
		targetname "Hane_Debug"
		symbols "on"

		links {
			-- projects
			"GLFW",         -- oznacavamo da Hane zavisi od GLFW tako da se prvo builda GLFW
			"GLAD",
			--"glm",
			"stb_image",
			-- projects

			-- system libraries
			"opengl32",
			-- system libraries

			-- builded
			"glfw3_Debug",
			"glad_Debug",
			"stb_image_Debug",
			--"glm_Debug",
			-- builded
		}

	filter "configurations:Release"
		runtime "Release"
		targetname "Hane_Release"
		optimize "on"

		links {
			-- projects
			"GLFW",
			"GLAD",
			--"glm",
			"stb_image",
			-- projects

			-- system libraries
			"opengl32",
			-- system libraries

			-- builded
			"glfw3_Release",
			"glad_Release",
			"stb_image_Release",
			--"glm_Release",
			-- builded
		}

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

	files{
		"%{prj.location}/include/GLFW/glfw3.h",
		"%{prj.location}/include/GLFW/glfw3native.h",

		"%{prj.location}/src/glfw_config.h",
		"%{prj.location}/src/context.c",
		"%{prj.location}/src/init.c",
		"%{prj.location}/src/input.c",
		"%{prj.location}/src/monitor.c",
		"%{prj.location}/src/vulkan.c",
		"%{prj.location}/src/window.c",

		"%{prj.location}/src/*.c" -- think about this line, do i realy need to include all???
	}

	defines{ 
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

----------------
--    GLAD    --
----------------

project "GLAD"
	location "../Hane/vendor/glad"
	kind "StaticLib"
	language "C"
	staticruntime "On" -- Sets <RuntimeLibrary> to "MultiThreaded" -- Sets at command line "/MT" for Release and "/MTd" for Debug

	targetdir ("%{prj.location}/bin/%{cfg.architecture}/%{cfg.buildcfg}"    )
	objdir (   "%{prj.location}/bin-int/%{cfg.architecture}/%{cfg.buildcfg}")

	files{
		"%{prj.location}/include/glad/glad.h",
		"%{prj.location}/include/glad/glad.c",

		"%{prj.location}/include/KHR/khrplatform.h",
	}

	includedirs{
		"%{IncludeDir.glad}",
		"%{IncludeDir.KHR}"
	}

	filter "configurations:Debug"
		runtime "Debug"
		targetname "glad_Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		targetname "glad_Release"
		optimize "on"

	filter "system:windows"
		systemversion "latest" -- Windows SDK Version

---------------------
--    stb_image    --
---------------------

project "stb_image"
	location "../Hane/vendor/stb_image"
	kind "StaticLib"
	language "C"
	staticruntime "On"

	targetdir ("%{prj.location}/bin/%{cfg.architecture}/%{cfg.buildcfg}"    )
	objdir (   "%{prj.location}/bin-int/%{cfg.architecture}/%{cfg.buildcfg}")

	files{
		"%{prj.location}/include/stb_image.h",
		"%{prj.location}/include/stb_image.cpp"
	}

	includedirs{
		"%{IncludeDir.stb_image}",
	}

	filter "configurations:Debug"
		runtime "Debug"
		targetname "stb_image_Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		targetname "stb_image_Release"
		optimize "on"

	filter "system:windows"
		systemversion "latest" -- Windows SDK Version

---------------
--    glm    --
---------------

--project "glm"
	--location "../Hane/vendor/glm"
	--kind "StaticLib"
	--language "C++"
	--cppdialect "C++17"
	--staticruntime "on"

	--targetdir ("%{prj.location}/bin/%{cfg.architecture}/%{cfg.buildcfg}"    )
	--objdir (   "%{prj.location}/bin-int/%{cfg.architecture}/%{cfg.buildcfg}")

	--defines{
		--"GLM_ENABLE_EXPERIMENTAL",
	--}

	--files{
		--"%{prj.location}/glm/**.hpp",
		--"%{prj.location}/glm/**.inl",
	--}

	--includedirs{
		--"%{IncludeDir.glm}",
	--}

	--filter "configurations:Debug"
		--runtime "Debug"
		--targetname "glm_Debug"
		--symbols "on"

	--filter "configurations:Release"
		--runtime "Release"
		--targetname "glm_Release"
		--optimize "on"

	--filter "system:windows"
		--systemversion "latest" -- Windows SDK Version

--------------------
--    premake5    --
--------------------

project "premake5"
	location ""
	kind "None" -- None or Utility https://premake.github.io/docs/kind/

	targetdir ("")
	objdir ("")

	files{
		"%{prj.location}/premake5.lua",
		"../Start.bat" -- to build solution RUN
	}