add_library(core 
	Board.cpp
	GameState.cpp
	Tile.cpp
)

target_include_directories(core
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)