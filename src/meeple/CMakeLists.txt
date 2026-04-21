add_library(meeple 
	Meeple.cpp
)

target_link_directories(meeple 
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(meeple 
	PUBLIC 
		tiles
)