workspace "DS"
    architecture "x64"
    -- startproject "Exp01-ProcessScheduling"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Winter"

-- group "Spring"
--     include "Spring/Exp01-ProcessScheduling"
--     include "Spring/Exp02-Deadlock"
--     include "Spring/Exp03-PagedMemoryManagement"
--     include "Spring/Exp04-FileSystem"
-- group ""