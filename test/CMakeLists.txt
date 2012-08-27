cmake_minimum_required( VERSION 2.8 )
project( FWMS-test )

find_package( Boost 1.46 REQUIRED thread unit_test_framework )

if( NOT Boost_USE_STATIC_LIBS )
	add_definitions( -DBOOST_TEST_DYN_LINK )
endif()

set( SRC_DIR "src" )
set( INC_DIR "src" )

set(
	SOURCES
	${INC_DIR}/ExampleReader.hpp
	${SRC_DIR}/ExampleReader.cpp
	${SRC_DIR}/Test.cpp
	${SRC_DIR}/TestMessage.cpp
	${SRC_DIR}/TestProperty.cpp
	${SRC_DIR}/TestReader.cpp
	${SRC_DIR}/TestRouter.cpp
)

include_directories( ${PROJECT_SOURCE_DIR}/../include )
include_directories( ${Boost_INCLUDE_DIRS} )

add_executable( test ${SOURCES} )

target_link_libraries( test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
target_link_libraries( test ${Boost_THREAD_LIBRARY} )
target_link_libraries( test fwms )

add_custom_command(
	TARGET test
	COMMAND test
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
