add_library(game_of_life STATIC 
	"cell.cpp"
	"colony.cpp"
)

add_executable(main main.cpp SDL_Utils.cpp)
target_link_libraries(main PRIVATE SDL3::SDL3 m game_of_life)
