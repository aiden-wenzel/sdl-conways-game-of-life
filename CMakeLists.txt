# set cmake standards
cmake_minimum_required(VERSION 3.10)
project(conways_game_of_life)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g3")

# fetch google test
include(FetchContent)

FetchContent_Declare(
	sdl
	URL https://github.com/libsdl-org/SDL/releases/download/release-3.2.4/SDL3-3.2.4.tar.gz
)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
)

FetchContent_Declare(
	imgui
	URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.9b.tar.gz
)

add_library(imgui STATIC
	"./build/_deps/imgui-src/imgui.cpp"
	"./build/_deps/imgui-src/imgui_demo.cpp"
	"./build/_deps/imgui-src/imgui_draw.cpp"
	"./build/_deps/imgui-src/imgui_tables.cpp"
	"./build/_deps/imgui-src/imgui_widgets.cpp"
	"./build/_deps/imgui-src/backends/imgui_impl_sdl3.cpp"
	"./build/_deps/imgui-src/backends/imgui_impl_sdlrenderer3.cpp"
)

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(sdl)
FetchContent_MakeAvailable(imgui)

include_directories("./build/_deps/sdl-src/include/")
include_directories("./build/_deps/googletest-src/googletest/include/")
include_directories("./build/_deps/imgui-src/")
include_directories("./build/_deps/imgui-src/backends/")
include_directories("./src")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(src)
add_subdirectory(test)
