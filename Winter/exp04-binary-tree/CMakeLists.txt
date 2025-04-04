cmake_minimum_required(VERSION 3.25)
project(Winter-Exp04-BinaryTree)

file(GLOB_RECURSE SOURCE_FILES *.cpp *.c)
file(GLOB_RECURSE HEADER_FILES *.hpp *.h)

set(ALL_FILES ${SOURCE_FILES} ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_FILES})

set(TARGET_NAME ${PROJECT_NAME})
add_executable(${TARGET_NAME} ${ALL_FILES})

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include) 

target_link_libraries(${TARGET_NAME} PRIVATE Utils)

set(EXPERIMENT_WORKING_DIR ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${TARGET_NAME} PRIVATE EXPERIMENT_WORKING_DIR="${EXPERIMENT_WORKING_DIR}")

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Winter")

