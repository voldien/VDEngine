CMAKE_MINIMUM_REQUIRED( VERSION 3.11.0 FATAL_ERROR )
PROJECT(vdengine VERSION 0.11.1 LANGUAGES CXX C)
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
	
	#TODO determine if can be done auto.
	#SET(FRAG_CORE_INCLUDE "${PROJECT_SOURCE_DIR}/extern/repo/fragengine/frag-core/include")
	#SET(FRAG_ENGINE_INCLUDE "${PROJECT_SOURCE_DIR}/extern/repo/fragengine/frag-engine/include")
	#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/extern/fragengine EXCLUDE_FROM_ALL)
ELSE()

ENDIF()


# GCC compiler flag options.
IF((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW)
	IF (BUILD_SHARED_LIBS AND CMAKE_SIZEOF_VOID_P EQUAL 8) # -fPIC is only required
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
	ENDIF()

	# 
	ADD_DEFINITIONS(-Wall -w -fpermissive) 
	ADD_DEFINITIONS( -export-dynamic -rdynamic -lstdc++fs -std=c++17 )

	IF (CMAKE_BUILD_TYPE STREQUAL "Release")
		MESSAGE(STATUS "Compile for release.")
		ADD_DEFINITIONS(-DNDEBUG=1)
		ADD_DEFINITIONS(-O3)
		SET(CMAKE_RELEASE TRUE)
		SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
	ELSE()
		MESSAGE(STATUS "Compile for debug.")
		ADD_DEFINITIONS(-D_DEBUG)
		ADD_DEFINITIONS(-g3 -O0)
		SET(CMAKE_DEBUG TRUE)
		ADD_DEFINITIONS(-D_GLIBCXX_ASSERTIONS)
	ENDIF()

	#
	IF(BUILD_WITH_COVERAGE)
		MESSAGE(STATUS "Building with coverage")
		SET(GCC_COVERAGE_COMPILE_FLAGS "--coverage -fprofile-arcs -ftest-coverage")
		SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
		SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
		SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
		SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
	ENDIF()

	#
	IF(BUILD_WITH_PROFILER)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
		SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
		SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
	ENDIF()
ELSEIF ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
  SET(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long ${CMAKE_CXX_FLAGS}" )
  SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
ELSEIF(MSVC)
	# Enable multi-core compilation with MSVC
	IF( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" ) # clang-cl
		ADD_COMPILE_OPTIONS(/bigobj /W4 /WX )
	ELSE() # msvc
		ADD_COMPILE_OPTIONS(/MP /bigobj /W4 /WX)
	ENDIF()

	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_DEBUG /Zi /Od")
ELSEIF ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
	SET(CMAKE_CXX_FLAGS "-g -fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long ${CMAKE_CXX_FLAGS}" )
	SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
ELSEIF( CMAKE_COMPILER_IS_MINGW )
	SET(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long -Wa,-mbig-obj ${CMAKE_CXX_FLAGS}")
	SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
	ADD_DEFINITIONS( -U__STRICT_ANSI__ )
ELSE()

ENDIF()


IF(BUILD_WITH_EXTERNAL_PROJECT)

	# Git must be avaiable on the system for using the external projects.
	IF(GIT_FOUND)
		INCLUDE(ExternalProject)
		SET_PROPERTY(DIRECTORY PROPERTY EP_STEP_TARGETS build)

		# Download the HPMCPP library.
		SET(HPMCPP_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/hpmcpp)
		SET(HPMCPP_LIB_DIR ${HPMCPP_ROOT}/lib)
		SET(HPMCPP_INCLUDE_DIR ${HPMCPP_ROOT}/include)
		ExternalProject_Add(hpmcpp-external
				URL ${CMAKE_CURRENT_SOURCE_DIR}/extern/hpmcpp
				SOURCE_DIR ${HPMCPP_ROOT}/src/hpmcpp
				BINARY_DIR ${HPMCPP_ROOT}/src/hpmcpp-build
				INSTALL_DIR ${HPMCPP_ROOT}
				CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DGIT_SUBMODULE=OFF
				STEP_TARGETS hpm-external build
				COMMENT "Building HPM-CPP"
				LOG_DOWNLOAD ON)
		# Include HPMCPP headers.
		ADD_LIBRARY(hpmcpp SHARED IMPORTED)
		ADD_DEPENDENCIES(hpmcpp hpmcpp-external)
		SET_TARGET_PROPERTIES(hpmcpp PROPERTIES
				IMPORTED_LOCATION ${HPMCPP_LIB_DIR}/libhpmcpp.so
				INTERFACE_LINK_LIBRARIES ${HPMCPP_LIB_DIR}/libhpmcpp.so
				INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/extern/hpmcpp/include)
		SET(HPMCPP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/extern/hpmcpp/include")
		SET(HPM_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/extern/hpmcpp/extern/hpm/include")

	ELSE()
		MESSAGE(FATAL_ERROR "Require Git for loading external projects.")
	ENDIF()
ENDIF()


# Define all file lists.
FILE(GLOB SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/audio/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/physic/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/tools/*.cpp)
FILE(GLOB HEADER_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Core/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Asset/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Audio/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Misc/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/DataStructure/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Physic/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Rendering/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Scene/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Tools/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Utility/*.h)
# Public headers - subset of header files.
FILE(GLOB DEVELOPMENT_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Core/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Asset/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Audio/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Misc/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/DataStructure/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Physic/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Rendering/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Scene/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Tools/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Utility/*.h)

# Core library for adding support for plugin.
ADD_LIBRARY(vdengine ${SOURCE_FILES} ${HEADER_FILES}
 							${OPEN_SIMPLEX_NOISE_SOURCE} ${PCG_C_BASIC_SOURCE}
							${RECASTNAVIGATION_SOURCE} ${POLYPARITION_SOURCE} ${KISS_FFT_SOURCE}
							${MISC_SOURCE} ) #${ZSTD_SOURCE}
SET_TARGET_PROPERTIES(vdengine PROPERTIES
		COMPILE_FLAGS "${JSONC_CFLAGS_OTHER} ${SDL2_CFLAGS_OTHER} ${AVFORMAT_CFLAGS_OTHER} ${AVCODEC_CFLAGS_OTHER}
		${AVUTIL_CFLAGS_OTHER} ${SWSCALE_CFLAGS_OTHER} ${ZIP_CFLAGS_OTHER}")
	set_property(TARGET vdengine PROPERTY CXX_STANDARD 20)
target_compile_features(vdengine PUBLIC c_std_11 cxx_std_20)
TARGET_LINK_LIBRARIES(vdengine ${SDL2_LIBRARIES} ${ZLIB_LIBRARIES} ${LIBXML2_LIBRARIES} ${Backtrace_LIBRARIES} ${FREETYPE_LIBRARIES}
		${ZIP_LIBRARIES} freeimage m dl ${JSONC_LIBRARIES} yaml hpmcpp ${OPENSSL_CRYPTO_LIBRARY}
		${AVFORMAT_LIBRARIES} ${AVCODEC_LIBRARIES} ${SWSCALE_LIBRARIES} ) #${ASSIMP_LIBRARIES} TODO relocate
ADD_DEPENDENCIES(vdengine hpmcpp)
TARGET_COMPILE_DEFINITIONS(vdengine PRIVATE VDENGINE_INTERNAL_IMP=1)	#TODO possible to be remove and handled by the source files completly.

#
TARGET_INCLUDE_DIRECTORIES(vdengine PRIVATE ${SDL2_INCLUDE_DIRS} ${ZIP_INCLUDE_DIRS} ${JSONC_INCLUDE_DIRS}
													 ${NANOSVG_INCLUDE_DIRS} ${RECASTNAVIGATION_INCLUDE_DIRS} ${NANOSVG_INCLUDE_DIRS}
													 ${OPEN_SIMPLEX_NOISE_INCLUDE_DIRS} ${PCG_C_BASIC_INCLUDE_DIRS} ${XATLAS_INCLUDE_DIRS}
													 ${KISS_FFT_INCLUDE_DIRS} ${MISC_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${Backtrace_INCLUDE_DIRS}
													 ${ZLIB_INCLUDE_DIRS} ${ZSTD_INCLUDE_DIRS} ${HPMCPP_INCLUDE_DIRS} ${HPM_INCLUDE_DIRS}  PUBLIC ${DEVELOPMENT_HEADER_FILES})
TARGET_INCLUDE_DIRECTORIES (vdengine PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
# Create package information
#CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/fragcore.pc.in" "${PROJECT_BINARY_DIR}/fragcore.pc" @ONLY)
