cmake_minimum_required(VERSION 2.6)
project(genom-4 CXX C)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")
add_executable(../bin/exec.out src/main.cpp)
target_link_libraries(../bin/exec.out m)

find_package(Doxygen)
add_custom_target(inputFiles
	${Doxygen_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
VERBATIM)
