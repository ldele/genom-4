cmake_minimum_required(VERSION 2.8.1)
project(genom-4 CXX C)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11 -pthread")

enable_testing()
include_directories(extlib/googletest/include extlib/googletest)
link_directories(extlib/googletest/build)

add_executable(../bin/exec.out src/main.cpp src/PWM.cpp src/DNA.cpp src/Interface.cpp src/SeqData.cpp)
#add_executable(../bin/unit_tests src/SuperDNAReader.cpp tests/tests.cpp)

target_link_libraries(../bin/exec.out m)
#target_link_libraries(../bin/unit_tests gtest gtest_main)
#add_test(unit_tests ../bin/unit_tests)

find_package(Doxygen)
add_custom_target(doc
	${Doxygen_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
VERBATIM)
