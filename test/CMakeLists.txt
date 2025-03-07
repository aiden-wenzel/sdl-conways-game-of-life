add_executable(cell_test cell_test.cpp "../src/cell.cpp")
target_link_libraries(cell_test gtest_main)
add_test(cell_test cell_test)
