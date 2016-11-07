cmake_minimum_required(VERSION 2.6)
project(genom-4 CXX C)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")
add_executable(../bin/exec.out src/main.cpp src/PWM.cpp)
target_link_libraries(../bin/exec.out m)

find_package(Doxygen)
add_custom_target(doc
	${Doxygen_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
VERBATIM)

enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(unittest bad_pwm_badFileStructure01.mat bad_pwm_badFileStructure02.mat)
target_link_libraries(unittest gtest gtest_main)
add_test(unittest)
