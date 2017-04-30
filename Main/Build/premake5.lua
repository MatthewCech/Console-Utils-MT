local ROOT = "../"   -- Path to project root

---------------------------------
-- [ WORKSPACE CONFIGURATION   --
---------------------------------
workspace "Canvases_MT"                         -- Solution Name
  configurations { "Debug", "Release", "Lib"}  -- Optimization/General config mode in VS
  platforms { "x64", "x86"}                    -- Dropdown platforms section in VS
  
  local proj_action = "UNDEFINED"

  -- _ACTION is the argument passed into premake5 when you run it.
  if _ACTION ~= nill then
    proj_action = _ACTION
  end

  location (ROOT .. "project_" .. proj_action)

  -------------------------------
  -- [ COMPILER/LINKER CONFIG] --
  -------------------------------
  
  flags "FatalWarnings"  -- Warnings to 11! (all warnings on)
  warnings "Extra"       -- Extra warnings, such as unused variables

  filter { "platforms:*86" } architecture "x86"
  filter { "platforms:*64" } architecture "x64"

  filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On"
  filter "configurations:Release"  defines { "NDEBUG" } optimize "On"
  filter "configurations:Lib"      defines { "NDEBUG", "STATIC_LIB" } optimize "On"

  filter { "action:gmake" }
    toolset "clang"
    buildoptions { "-std=c++14" }
    
  filter {} -- clear filter
  language "C++"

  -------------------------------
  -- [ PROJECT CONFIGURATION ] --
  ------------------------------- 
  project "Canvases_MT"        -- Project name
    filter "configurations:not Lib"
      targetname "ascii_draw" -- Executable name
      kind "ConsoleApp"      -- Style of app in project- WindowedApp, ConsoleApp, etc.
    
    filter "configurations:Lib"
      targetname "canvas"
      kind "StaticLib"

    filter {} -- clear filter


  ------------------------------
  -- [ BUILD CONFIGURATIONS ] --
  ------------------------------

    -- Set the rpath on the executable, to allow for relative path for dynamic lib
    filter { "system:macosx", "action:gmake" }
      linkoptions { "-rpath @executable_path/lib" }

    filter { "system:linux", "action:gmake" }
      buildoptions { "-stdlib=libc++" }     -- linux needs more info
      linkoptions  { "-stdlib=libc++" }     
    
    -- when building any visual studio project
    filter { "system:windows", "action:vs*"}
      flags         { "MultiProcessorCompile", "NoMinimalRebuild" }
      linkoptions   { "/ignore:4099" }      -- Ignore library pdb warnings when running in debug

    filter {} -- clear filter   

    ----------------------------------
    -- [ FILE PATH CONFIGURATIONS ] --
    ----------------------------------
    local source_dir              = ROOT .. "Source/"
    local output_dir_root         = ROOT .. "bin_%{cfg.platform}_%{cfg.buildcfg}_" .. proj_action .. "/"
    filter {"configurations:not Lib"} targetdir(output_dir_root) -- Where all output files are stored
    filter {"configurations:Lib"}     targetdir(output_dir_root .. "/lib_%{cfg.platform}")
    filter {} -- clear filter

    -- Files to be compiled (cpp) or added to project (visual studio)
    files
    {
      source_dir .. "**.c",
      source_dir .. "**.cpp",
      source_dir .. "**.h",
      source_dir .. "**.hpp",
      source_dir .. "**.tpp",
    }

    filter { "files:**.tpp" }
      flags {"ExcludeFromBuild"}

    vpaths {
      ["Headers"] = 
          { 
            source_dir .. "**.h", 
            source_dir .. "**.hpp"
          },
      ["Sources/*"] = 
        {
          source_dir .. "**.c", 
          source_dir .. "**.cpp", 
          source_dir .. "**.tpp"
        },
      ["Docs"] = "**.txt"
    }


filter {} -- clear filter

