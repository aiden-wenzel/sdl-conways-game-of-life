# set cmake standards
cmake_minimum_required(VERSION 3.10)
project(conways_game_of_life)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g3")

file(GLOB SOURCES "deps/imgui/*.cpp")
add_library(
	imgui STATIC ${SOURCES} 
	"deps/imgui/backends/imgui_impl_sdl3.cpp"
	"deps/imgui/backends/imgui_impl_sdlrenderer3.cpp"
)

include_directories("deps/imgui/")
include_directories("deps/imgui/backends/")
include_directories("deps/googletest/googletest/include")
include_directories("./src")
include_directories("include")
include_directories("deps/SDL/include")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(deps/SDL)
add_subdirectory(deps/googletest)
add_subdirectory(src)
add_subdirectory(test)
