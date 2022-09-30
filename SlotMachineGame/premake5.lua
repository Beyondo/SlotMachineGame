project "SlotMachineGame"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	targetname "SlotMachine"

	targetdir ("%{wks.location}/Out/Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Out/Obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.hpp",
	}

	includedirs
	{
		"src",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.SFML}",
	}
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"3rdparty/SFML/lib/**.lib",
		"opengl32.lib"
	}
	postbuildcommands
	{
	  "{COPY} assets %{cfg.targetdir}/assets",
	  "{COPY} 3rdparty/SFML/bin/openal32.dll /",
	  "{COPY} 3rdparty/SFML/bin/openal32.dll %{cfg.targetdir}"
	}
	filter "system:windows"
		systemversion "latest"

	defines "INITGUID"
	filter "configurations:Debug"
		defines "OCTAVIAN_DEBUG"
		runtime "Debug"
		symbols "on"
		postbuildcommands
		{
			"{COPY} 3rdparty/SFML/bin/sfml-audio-d-2.dll /",
			"{COPY} 3rdparty/SFML/bin/sfml-audio-d-2.dll %{cfg.targetdir}"
		}

	filter "configurations:Release"
		defines "OCTAVIAN_RELEASE"
		runtime "Release"
		optimize "on"
		postbuildcommands
		{
			"{COPY} 3rdparty/SFML/bin/sfml-audio-2.dll /",
			"{COPY} 3rdparty/SFML/bin/sfml-audio-2.dll %{cfg.targetdir}"
		}

	filter "configurations:Distribution"
		defines "OCTAVIAN_DIST"
		runtime "Release"
		optimize "on"
