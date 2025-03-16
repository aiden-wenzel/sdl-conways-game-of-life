add_library(game_of_life STATIC 
	"colony.cpp"
	"SDL_Utils.cpp"
	"mouse.cpp"
)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE SDL3::SDL3 m game_of_life)
