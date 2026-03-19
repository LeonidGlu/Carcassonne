add_library(tiles 
	Tile.cpp
	TileData.cpp
	TileFactory.cpp
)

target_include_directories(tiles 
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)