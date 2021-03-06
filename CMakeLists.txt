cmake_minimum_required( VERSION 2.8 )
project( FWMS )

set( FWMS_BUILD_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries." )
set( FWMS_BUILD_TEST TRUE CACHE BOOL "Build test suite." )
#set( FWMS_BUILD_EXAMPLES TRUE CACHE BOOL "Build examples." )
set( FWMS_BUILD_DOCS FALSE CACHE BOOL "Build Doxygen API documentation." )
set( FWMS_SKIP_INSTALL FALSE CACHE BOOL "Do not run install target (useful when including lib in projects)." )

if( FWMS_BUILD_SHARED_LIBS )
	set( LIB_TYPE SHARED )
else()
	set( LIB_TYPE STATIC )
endif()

if( CMAKE_COMPILER_IS_GNUCXX )
	if( NOT CMAKE_CXX_FLAGS )
		set( CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Wconversion -pedantic" CACHE STRING "C++ compiler flags." FORCE )
	endif()
endif()

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type." FORCE )
endif()

set( SRC_DIR "src" )
set( INC_DIR "include" )

set(
	SOURCES
	"${INC_DIR}/FWMS/Config.hpp"
	"${INC_DIR}/FWMS/Hash.hpp"
	"${INC_DIR}/FWMS/Message.hpp"
	"${INC_DIR}/FWMS/Message.inl"
	"${INC_DIR}/FWMS/Property.hpp"
	"${INC_DIR}/FWMS/Property.inl"
	"${INC_DIR}/FWMS/Reader.hpp"
	"${INC_DIR}/FWMS/ReaderLink.hpp"
	"${INC_DIR}/FWMS/Router.hpp"
	"${SRC_DIR}/FWMS/Config.cpp"
	"${SRC_DIR}/FWMS/Hash.cpp"
	"${SRC_DIR}/FWMS/Message.cpp"
	"${SRC_DIR}/FWMS/Property.cpp"
	"${SRC_DIR}/FWMS/Reader.cpp"
	"${SRC_DIR}/FWMS/ReaderLink.cpp"
	"${SRC_DIR}/FWMS/Router.cpp"
)

include_directories( ${INC_DIR} )
add_library( fwms ${LIB_TYPE} ${SOURCES} )

if( FWMS_BUILD_SHARED_LIBS )
	set_target_properties( fwms PROPERTIES DEBUG_POSTFIX -d )
else()
	set_target_properties( fwms PROPERTIES DEBUG_POSTFIX -s-d )
	set_target_properties( fwms PROPERTIES RELEASE_POSTFIX -s )
	set_target_properties( fwms PROPERTIES MINSIZEREL_POSTFIX -s )
endif()


if( NOT FWMS_SKIP_INSTALL )
	install(
		TARGETS fwms
		RUNTIME DESTINATION bin COMPONENT bin
		LIBRARY DESTINATION lib COMPONENT bin
		ARCHIVE DESTINATION lib COMPONENT dev
	)

	install(
		DIRECTORY include/FWMS
		DESTINATION include
	)
endif()

if( FWMS_BUILD_TEST )
	add_subdirectory( test )
endif()

#if( FWMS_BUILD_EXAMPLES )
#	add_subdirectory( examples )
#endif()

if( FWMS_BUILD_DOCS )
	add_subdirectory( "doc/doxygen" )
endif()
