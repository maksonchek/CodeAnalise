cmake_minimum_required(VERSION 3.22.2 FATAL_ERROR)

set(PROJECT_NAME CodeAnalise)

project (${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp)

add_subdirectory(external/matplotplusplus)
target_link_libraries(${PROJECT_NAME} PUBLIC matplot)
