cmake_minimum_required(VERSION 3.25)
project(Utils)

file(GLOB_RECURSE SOURCE_FILES *.cpp *.c)
file(GLOB_RECURSE HEADER_FILES *.hpp *.h)

set(ALL_FILES ${SOURCE_FILES} ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_FILES})

set(LIBRARY_NAME Utils)
# if (MSVC)
#     # NOTE: Using dynamic linking on Windows is not recommended.
#     add_library(${LIBRARY_NAME} STATIC ${ALL_FILES})
# else()
#     add_library(${LIBRARY_NAME} SHARED ${ALL_FILES})
# endif()
add_library(${LIBRARY_NAME} INTERFACE)

target_include_directories(
    # ${LIBRARY_NAME} PUBLIC
    ${LIBRARY_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# target_compile_definitions(${LIBRARY_NAME}
#     PRIVATE $<$<BOOL:${BUILD_SHARED_LIBS}>:UTILS_EXPORT>
#     INTERFACE $<$<BOOL:${BUILD_SHARED_LIBS}>:UTILS_IMPORT>
# )