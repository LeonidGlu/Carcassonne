add_library(core 
	Board.cpp
	GameState.cpp
	Tile.cpp
	MoveGenerator.cpp
	PlacementValidator.cpp
	RegionManager.cpp
	ScoreCalculator.cpp "TypedRegion.cpp")

target_include_directories(core
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)