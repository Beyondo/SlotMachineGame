project "SFML"
	kind "StaticLib"
	language "C++"

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
		"include",
		"src",
		"extlibs/headers/AL"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"