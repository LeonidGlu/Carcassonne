cmake_minimum_required (VERSION 3.16)

project(Carcassonne VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src/core)
add_subdirectory(src/graph)

add_executable(Carcassonne
	src/main.cpp
 "include/core/RegionManager.h" "include/core/PlacementValidator.h" "include/core/MoveGenerator.h" "include/core/ScoreCalculator.h" "include/core/TypedRegion.h")

target_link_libraries(Carcassonne
	PRIVATE
		core
		graph
)
