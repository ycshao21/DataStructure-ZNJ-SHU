cmake_minimum_required(VERSION 3.25)
project(DataStructure-ZNJ-SHU)

set(USE_SOLUTION_FOLDERS ON)
set(GROUP_BY_EXPLORER ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add experiment folders
add_subdirectory(winter)
# add_subdirectory(spring)

# Add utils library
add_subdirectory(utils)

if(MSVC)
  set(STARTUP_PROJECT Winter-Exp01-InterviewArrangement)
  set_property(TARGET ${STARTUP_PROJECT} PROPERTY VS_STARTUP_PROJECT ${STARTUP_PROJECT})
endif()