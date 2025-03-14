add_executable(cell_test cell_test.cpp)
target_link_libraries(cell_test gtest_main game_of_life)
add_test(cell_test cell_test)

add_executable(colony_test colony_test.cpp)
target_link_libraries(colony_test gtest_main game_of_life)
add_test(colony_test colony_test)

add_executable(render_cell_test render_cell.cpp ../src/SDL_Utils.cpp)
target_link_libraries(render_cell_test PUBLIC game_of_life PRIVATE SDL3::SDL3)
