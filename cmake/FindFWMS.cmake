#
# Find FWMS library.
#
# Input variables:
#   FWMS_ROOT              Additional library search directory.
#   FWMS_STATIC_LIBRARIES  Look for static libraries.
#
# Output variables:
#   FWMS_INCLUDE_DIR   Include directory.
#   FWMS_LIBRARY       Library.

cmake_minimum_required( VERSION 2.8 )

set( FWMS_FOUND FALSE )

if( FWMS_STATIC_LIBRARIES )
	set( FWMS_SUFFIX "-s" )
	add_definitions( -DFWMS_STATIC )
else()
	set( FWMS_SUFFIX "" )
endif()

find_path(
	FWMS_INCLUDE_DIR
	FWMS/Config.hpp
	PATH_SUFFIXES
		include
	PATHS
		/usr
		/usr/local
		${FWMS_ROOT}
)

find_library(
	FWMS_LIBRARY_RELEASE
	FWMS${FWMS_SUFFIX}
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${FWMS_ROOT}
)

find_library(
	FWMS_LIBRARY_DEBUG
	fwms${FWMS_SUFFIX}-d
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${FWMS_ROOT}
)

if( FWMS_LIBRARY_RELEASE AND FWMS_LIBRARY_DEBUG )
	set( FWMS_LIBRARY debug ${FWMS_LIBRARY_DEBUG} optimized ${FWMS_LIBRARY_RELEASE} )
elseif( FWMS_LIBRARY_RELEASE )
	set( FWMS_LIBRARY ${FWMS_LIBRARY_RELEASE} )
elseif( FWMS_LIBRARY_DEBUG )
	set( FWMS_LIBRARY ${FWMS_LIBRARY_DEBUG} )
endif()

if( NOT FWMS_INCLUDE_DIR OR NOT FWMS_LIBRARY )
	message( FATAL_ERROR "FWMS not found." )
else()
	message( "FWMS found: ${FWMS_INCLUDE_DIR}" )
endif()
