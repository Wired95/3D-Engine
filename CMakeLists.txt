project(3DEngine)

cmake_minimum_required(VERSION 2.8)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

file(GLOB_RECURSE source_files src/* )

add_executable(3DEngine ${source_files})

add_subdirectory(dep/SDL2)

include_directories(dep/SDL2/include)

if((${CMAKE_BUILD_TYPE} MATCHES "") OR (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    add_definitions("-static")
endif()

add_dependencies(3DEngine SDL2)
add_dependencies(3DEngine SDL2main)

target_link_libraries(3DEngine SDL2)
target_link_libraries(3DEngine SDL2main)