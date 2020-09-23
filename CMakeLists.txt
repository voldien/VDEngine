CMAKE_MINIMUM_REQUIRED( VERSION 3.11.0 FATAL_ERROR )
PROJECT(vdengine VERSION 0.11.1 LANGUAGES C CXX)
# Build shared/dynamic library option
OPTION(BUILD_SHARED_LIBS "Build package with shared libraries." ON)
OPTION(BUILD_WITH_COVERAGE "Enable profiling and coverage report analysis." OFF)
OPTION(BUILD_WITH_PROFILER "Enable profiling." OFF)
OPTION(BUILD_WITH_EXTERNAL_PROJECT "Enable external project build." ON)
OPTION(BUILD_WITH_INSTALL "Disable this if you want to use fragengine as a submodule." ON )
OPTION(BUILD_WITH_UBSAN "" OFF)
OPTION(BUILD_WITH_ASAN "Enable AddressSanitizer." OFF )
OPTION(BUILD_OPT_BUILD_PACKAGES "Set to ON to generate CPack configuration files and packaging targets" OFF)
OPTION(BUILD_WITH_DEBUG_BOUNDSCHECK "Array/Pointer BoundsChecking, buffer overflow protection. Used in debug only." OFF)
option(BUILD_INSTALL_RESOURCES "Installs the Resources directory" ON)
IF(NOT BUILD_SHARED_LIBS)
	SET(CMAKE_EXE_LINKER_FLAGS "-static")
	SET(LINK_SEARCH_START_STATIC TRUE)
ELSE()
	MESSAGE(STATUS "Shared libraries enabled")
ENDIF(NOT BUILD_SHARED_LIBS)


# Set version of the project.
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 1)
SET(VERSION_REVISION 0)
SET(VERSION_STATE a)
SET(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}${VERSION_STATE}${VERSION_REVISION} )
SET(PROJECT_VERSION "${VERSION}")
ADD_DEFINITIONS(-DFV_VERSION="${VERSION}")

FIND_PACKAGE(Git QUIET)
SET(FRAGENGINE_SUBMODULE_PATH ${PROJECT_SOURCE_DIR}/extern/repo/fragengine)
IF(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	# Update submodules as needed
	OPTION(GIT_SUBMODULE "Check submodules during build" ON)
	IF(GIT_SUBMODULE)
		FILE(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/extern/repo/fragengine)
		MESSAGE(STATUS "Submodule update  --recursive")
		EXECUTE_PROCESS(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
						WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
						RESULT_VARIABLE GIT_SUBMOD_RESULT)
		IF(NOT GIT_SUBMOD_RESULT EQUAL "0")
			MESSAGE(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
		ENDIF()
	ENDIF()
	
	ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/extern/fragengine EXCLUDE_FROM_ALL)
ELSE()

ENDIF()

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/Engine)