include "Dependencies.lua"
workspace "SlotMachineGame"
	architecture "x86_64"
	startproject "SlotMachineGame"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "SlotMachineGame/3rdparty/GLFW"
	include "SlotMachineGame/3rdparty/Glad"
	include "SlotMachineGame/3rdparty/imgui"
group ""
	include "SlotMachineGame"