add_executable(colony_test colony_test.cpp)
target_link_libraries(colony_test gtest game_of_life)
add_test(colony_test colony_test)

add_executable(mouse_test mouse_test.cpp)
target_link_libraries(mouse_test gtest game_of_life)
add_test(mouse_test mouse_test)

add_executable(render_cell_test render_cell.cpp)
target_link_libraries(render_cell_test game_of_life)

add_executable(game_test game_test.cpp)
target_link_libraries(game_test game_of_life)

add_executable(mouse_input_test mouse_input_test.cpp)
target_link_libraries(mouse_input_test game_of_life)

add_executable(imgui_test imgui_test.cpp)
target_link_libraries(imgui_test SDL3::SDL3 imgui)

add_executable(my_imgui_test my_imgui_test.cpp)
target_link_libraries(my_imgui_test SDL3::SDL3 imgui)
