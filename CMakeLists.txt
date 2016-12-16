cmake_minimum_required(VERSION 2.8.1)
project(genom-4 CXX C)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11 -pthread")

option(main "Build app." OFF)
option(Qt "Build GUI." ON)
option(test "Build tests." OFF)

if(main)
	include_directories(src)
	link_directories(/usr/local/lib)

	add_executable(inter.out src/inter.cpp src/Interface.cpp src/DNA.cpp src/PWM.cpp src/SeqData.cpp)
	target_link_libraries(inter.out m)

endif(main)

if(Qt)
	find_package(Qt4)
	set(CMAKE_AUTOMOC ON)
	set(CMAKE_AUTOOUIC ON)
	include_directories(src /usr/include/qt4/Qt)
	link_directories(/usr/local/lib /usr/lib)

	add_executable(genom-4 src/main.cpp src/EditAbstract.cpp src/MainWindow.cpp src/Window.cpp src/EditDNA.cpp src/EditPWM.cpp 
						   src/Interface.cpp src/DNA.cpp src/PWM.cpp src/SeqData.cpp)

	target_link_libraries(genom-4 Qt4::QtGui png pthread)
endif(Qt)

if(test)
	enable_testing()
	find_package(GTest)
	include_directories(${GTEST_INCLUDE_DIRS})
	link_directories(extlib/googletest/build)

	#add_executable(../bin/unit_tests src/SuperDNAReader.cpp src/PWM.cpp tests/tests.cpp)
	add_executable(tests.out src/Interface.cpp src/PWM.cpp src/SeqData.cpp src/DNA.cpp tests/tests.cpp)
	target_link_libraries(tests.out gtest gtest_main)
	add_test(unit_tests tests.out)
endif(test)

find_package(Doxygen)
if(DOXYGEN_FOUND)
	add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/doc/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../doc
		COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
