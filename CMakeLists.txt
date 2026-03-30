cmake_minimum_required (VERSION 3.16)

project(Carcassonne VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_DEBUG "Enable debug output" OFF)

if(ENABLE_DEBUG)
    add_compile_definitions(DEBUG_MODE)
    message(STATUS "Debug mode: ON")
else()
    message(STATUS "Debug mode: OFF")
endif()

add_subdirectory(src/core)
add_subdirectory(src/graph)
add_subdirectory(src/game)
add_subdirectory(src/render)
add_subdirectory(src/tiles)
add_executable(Carcassonne
	src/main.cpp
 )

target_link_directories(Carcassonne
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(Carcassonne
	PRIVATE
		core
		game
		render
)
