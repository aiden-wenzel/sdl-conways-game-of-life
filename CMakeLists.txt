# set cmake standards
cmake_minimum_required(VERSION 3.10)
project(conways_game_of_life)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# fetch google test
include(FetchContent)

FetchContent_Declare(
	unity
	URL https://github.com/ThrowTheSwitch/Unity/archive/refs/tags/v2.6.1.tar.gz)

FetchContent_Declare(
	sdl
	URL https://github.com/libsdl-org/SDL/releases/download/release-3.2.4/SDL3-3.2.4.tar.gz
)

FetchContent_MakeAvailable(unity)
FetchContent_MakeAvailable(sdl)

include_directories("./build/_deps/sdl-src/include/")
include_directories("./build/_deps/unity-src/src")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(src)
add_subdirectory(test)
