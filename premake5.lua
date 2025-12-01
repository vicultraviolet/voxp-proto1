OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}"

workspace "Voxploration"
    architecture "x64"
    configurations { "dbg", "rel", "dist" }
    startproject "vxp"

    targetdir "bin/%{OUTPUT_DIR}/%{prj.name}/"
    objdir "bin-int/%{OUTPUT_DIR}/%{prj.name}/"

    debugdir "%{wks.location}"

NatriumDir = "%{wks.location}/natrium/"

include "natrium/Natrium-Premake.lua"
include "vxp/vxp-Premake.lua"
