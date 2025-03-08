add_executable(main main.cpp SDL_Utils.cpp)
target_link_libraries(main PRIVATE SDL3::SDL3 m)
