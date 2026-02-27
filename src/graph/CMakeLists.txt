add_library(graph
	Graph.cpp
	GraphAlgorithms.cpp
	UnionFind.cpp
)

target_include_directories(graph
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)