IncludeDir = {}
IncludeDir["GLFW"]                        = "%{wks.location}/Hane/vendor/GLFW/include"
							              
IncludeDir["glad"]                        = "%{wks.location}/Hane/vendor/glad/include"
IncludeDir["KHR"]                         = "%{wks.location}/Hane/vendor/KHR/include"

IncludeDir["imgui_dockingBranch"]         = "%{wks.location}/Hane/vendor/imgui_dockingBranch"

IncludeDir["stb_image"]                   = "%{wks.location}/Hane/vendor/stb_image/include"

-- forked math library https://github.com/bandit045/glm from https://github.com/g-truc/glm
IncludeDir["glm"] = "%{wks.location}/Hane/vendor/glm" -- Using only as project, does not compile with core, bcs its header template library

-------------------------------------------------------------------------------------------

LibraryDir = {}
LibraryDir["glfw3"]               = "%{wks.location}/Hane/vendor/GLFW/bin/%{cfg.architecture}/%{cfg.buildcfg}"
LibraryDir["glad"]                = "%{wks.location}/Hane/vendor/glad/bin/%{cfg.architecture}/%{cfg.buildcfg}"
LibraryDir["stb_image"]           = "%{wks.location}/Hane/vendor/stb_image/bin/%{cfg.architecture}/%{cfg.buildcfg}"
LibraryDir["imgui_dockingBranch"] = "%{wks.location}/Hane/vendor/imgui_dockingBranch/bin/%{cfg.architecture}/%{cfg.buildcfg}"

Library = {}
Library["glfw3"]                  = "%{LibraryDir.glfw3}/glfw3_%{cfg.buildcfg}.lib" -- ako je imamo u nasem solutionu onda dodajemo ovde,  u suprotnom kao sto je opengl32 onda samo navedemo u links
Library["glad"]                   = "%{LibraryDir.glad}/glad_%{cfg.buildcfg}.lib"
Library["stb_image"]              = "%{LibraryDir.stb_image}/stb_image_%{cfg.buildcfg}.lib"
Library["imgui_dockingBranch"]    = "%{LibraryDir.imgui_dockingBranch}/imgui_dockingBranch_%{cfg.buildcfg}.lib"

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

group "Dependencies/StaticLib"
	project "GLFW"
	project "GLAD"
	project "stb_image"
	project "imgui_dockingBranch"
group "Dependencies/TemplateLibrary"
	project "glm"

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

	files{ -- Which files to be included in project, filter VisualStudio

		"%{prj.location}/main.cpp",   -- Hane files
									  
		"%{prj.location}/src/**.h",   -- Hane files
		"%{prj.location}/src/**.cpp", -- Hane files
	}

	defines{
		"_CRT_SECURE_NO_WARNINGS", -- #ifndef GLM_ENABLE_EXPERIMENTAL error "GLM: GLM_GTX_associated_min_max is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it."
		"GLM_ENABLE_EXPERIMENTAL", -- for math library
	}

	includedirs{
		"%{IncludeDir.imgui_dockingBranch}",
		"%{IncludeDir.GLFW}",

		"%{IncludeDir.glad}",
		"%{IncludeDir.KHR}",

		"%{IncludeDir.glm}",

		"%{IncludeDir.stb_image}",
	}

	filter "configurations:Debug"
		runtime "Debug"
		targetname "Hane_Debug"
		symbols "on"

		links {
			-- projects
			"GLFW",         -- oznacavamo da Hane zavisi od GLFW tako da se prvo builda GLFW
			"GLAD",
			"stb_image",
			"imgui_dockingBranch",
			-- projects

			-- system libraries
			"opengl32",
			-- system libraries

			-- builded -- obsolete can be removed but make my life much more easier in long time span, when is explicit here
			"%{Library.glfw3}",
			"%{Library.glad}",
			"%{Library.stb_image}",
			"%{Library.imgui_dockingBranch}",
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
			"stb_image",
			"imgui_dockingBranch",
			-- projects

			-- system libraries
			"opengl32",
			-- system libraries

			-- builded
			"%{Library.glfw3}",
			"%{Library.glad}",
			"%{Library.stb_image}",
			"%{Library.imgui_dockingBranch}",
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

		"%{prj.location}/src/*.c" -- think about this line, do i realy need to include all??? https://youtu.be/88dmtleVywk?si=j6nCAN44hA2OKnbr&t=534
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

-------------------------------
--    imgui_dockingBranch    -- 
-------------------------------

project "imgui_dockingBranch"
	location "../Hane/vendor/imgui_dockingBranch"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On" -- Sets <RuntimeLibrary> to "MultiThreaded" -- Sets at command line "/MT" for Release and "/MTd" for Debug

	targetdir ("%{prj.location}/bin/%{cfg.architecture}/%{cfg.buildcfg}"    )
	objdir (   "%{prj.location}/bin-int/%{cfg.architecture}/%{cfg.buildcfg}")

	files{ -- Which files to be included in project, filter VisualStudio

		"%{prj.location}/*.h",
		"%{prj.location}/*.cpp",

		"%{prj.location}/backends/imgui_impl_glfw.h",
		"%{prj.location}/backends/imgui_impl_glfw.cpp",

		"%{prj.location}/backends/imgui_impl_opengl2.cpp",
		"%{prj.location}/backends/imgui_impl_opengl2.h",
		"%{prj.location}/backends/imgui_impl_opengl3.cpp",
		"%{prj.location}/backends/imgui_impl_opengl3.h",
		"%{prj.location}/backends/imgui_impl_opengl3_loader.h",
	}

	includedirs{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.imgui_dockingBranch}",
	}

	filter "configurations:Debug"
		runtime "Debug"
		targetname "imgui_dockingBranch_Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		targetname "imgui_dockingBranch_Release"
		optimize "on"

	filter "system:windows"
		systemversion "latest" -- Windows SDK Version

---------------
--    glm    -- 
---------------

-- glm is template library cant be compiled as a staticLib or dynamicLib :TODO add it to prch-precompiled header
project "glm"
	location "../Hane/vendor/glm"
	kind "None"

	-- makro is defined inside Hane project GLM_ENABLE_EXPERIMENTAL

	files{
		"%{prj.location}/**.hpp",
		"%{prj.location}/**.inl",
	}

--------------------
--    premake5    --
--------------------

project "premake5"
	location "" -- where lives premake5.exe
	kind "None" -- None or Utility https://premake.github.io/docs/kind/

	files{
		"%{prj.location}/premake5.lua",
		"../Start.bat" -- to build solution RUN, run it from Window Explorer
	}