add_executable(colony_test colony_test.cpp)
target_link_libraries(colony_test gtest_main game_of_life)
add_test(colony_test colony_test)

add_executable(render_cell_test render_cell.cpp)
target_link_libraries(render_cell_test PUBLIC game_of_life PRIVATE SDL3::SDL3)

add_executable(game_test game_test.cpp)
target_link_libraries(game_test PUBLIC game_of_life PRIVATE SDL3::SDL3)

add_executable(mouse_test mouse_input_test.cpp)
target_link_libraries(mouse_test PUBLIC game_of_life PRIVATE SDL3::SDL3)
