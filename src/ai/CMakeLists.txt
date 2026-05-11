add_library(ai
	GameStateSnapshot.cpp
	HeuristicEvaluator.cpp
)

target_include_directories(ai
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(ai
	PUBLIC
		core
		game
)