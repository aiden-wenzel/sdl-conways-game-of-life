add_library(game_of_life STATIC 
	"colony.cpp"
	"SDL_Utils.cpp"
	"mouse.cpp"
	"game.cpp"
)

target_link_libraries(game_of_life SDL3::SDL3 imgui)

add_executable(main main.cpp)
target_link_libraries(main m game_of_life)
