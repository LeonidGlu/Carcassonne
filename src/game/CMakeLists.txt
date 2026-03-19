add_library(game 
	Game.cpp
	Deck.cpp
	Player.cpp
)

target_include_directories(game 
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(game 
	PUBLIC
		core
		tiles
)