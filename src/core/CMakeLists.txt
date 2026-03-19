add_library(core 
	Board.cpp
	GameState.cpp
	MoveGenerator.cpp
	PlacementValidator.cpp
	RegionManager.cpp
	ScoreCalculator.cpp 
	TypedRegion.cpp
)

target_include_directories(core
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(core
	PUBLIC
		graph
		tiles
)