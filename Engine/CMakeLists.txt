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

# Get the include directories for the target.
GET_TARGET_PROPERTY(LIBFRAGCORE_INCLUDES fragcore INCLUDE_DIRECTORIES)
# GET_TARGET_PROPERTY(LIBHPM_INCLUDES hpm INCLUDE_DIRECTORIES)
# GET_TARGET_PROPERTY(LIBHPMCPP_INCLUDES hpmcpp INCLUDE_DIRECTORIES)

# Core library for adding support for plugin.
ADD_LIBRARY(vdengine ${SOURCE_FILES} ${HEADER_FILES})
SET_TARGET_PROPERTIES(vdengine PROPERTIES
		COMPILE_FLAGS "")
#SET_TARGET_PROPERTIES(TARGET vdengine PROPERTY CXX_STANDARD 20)
target_compile_features(vdengine PUBLIC cxx_std_20)
TARGET_LINK_LIBRARIES(vdengine m fragcore ${ASSIMP_LIBRARIES}) #${ASSIMP_LIBRARIES} TODO relocate
ADD_DEPENDENCIES(vdengine fragcore)
TARGET_COMPILE_DEFINITIONS(vdengine PRIVATE VDENGINE_INTERNAL_IMP=1)	#TODO possible to be remove and handled by the source files completly.
#
TARGET_INCLUDE_DIRECTORIES(vdengine PRIVATE ${KISS_FFT_INCLUDE_DIRS} ${MISC_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${LIBFRAGCORE_INCLUDES}
											${ZLIB_INCLUDE_DIRS} ${ZSTD_INCLUDE_DIRS} ${HPMCPP_INCLUDE_DIRS} ${HPM_INCLUDE_DIRS}  PUBLIC ${DEVELOPMENT_HEADER_FILES})
											
TARGET_INCLUDE_DIRECTORIES (vdengine PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
# Create package information
#CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/fragcore.pc.in" "${PROJECT_BINARY_DIR}/fragcore.pc" @ONLY)


# # Install binary program
# IF(BUILD_WITH_INSTALL)
# 	INSTALL(TARGETS fragview DESTINATION bin COMPONENT ${BINFRAGVIEW_COMPONENT})

# 	IF(UNIX)
# 		Find_PACKAGE(UnixCommands REQUIRED)

# 		# Generate compressed man page.
# 		ADD_CUSTOM_TARGET(mangzip
# 				COMMAND ${GZIP} -k -c ${CMAKE_CURRENT_SOURCE_DIR}/fragview.1 > ${CMAKE_CURRENT_SOURCE_DIR}/fragview.1.gz
# 				COMMENT "Compressing man page.")
# 		ADD_DEPENDENCIES(fragview mangzip)
# 		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.1.gz DESTINATION /usr/share/man/man1/)

# 		#TODO add spriv generating file.

# 		IF(ZIP)
# 			# TODO add addition for adding support for spirv and combine multiple files
# 			#get_filename_component(RELATIVE_SHADER_SOURCE "${PROJECT_SOURCE_DIR}/shaders" DIRECTORY BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
# 			#FIXME add for relative path.
# 			SET(RELATIVE_SHADER_SOURCE "shaders")
# 			ADD_CUSTOM_TARGET(	internal-shader-generation
# 					COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/shaders
# 					COMMAND ${CP} -r ${PROJECT_SOURCE_DIR}/shaders/* ${CMAKE_CURRENT_BINARY_DIR}/shaders/
# 					COMMAND zip -r ${SHADERZIPFILE} ${RELATIVE_SHADER_SOURCE}/
# 					COMMAND ${RM} -r ${CMAKE_CURRENT_BINARY_DIR}/shaders
# 					COMMENT "Created Asset file")
# 			ADD_DEPENDENCIES(fragview internal-shader-generation)
# 			INSTALL( FILES ${SHADERZIPFILE} DESTINATION /usr/share/fragview )
# 		ELSE()

# 		ENDIF()

# 		# Install scripts
# 		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/scripts/newshad.sh DESTINATION /usr/share/fragview/ )
# 		ADD_DEFINITIONS(-DICON_LOCATION="/usr/share/fragview/")

# 		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png DESTINATION /usr/share/fragview/ )
# 		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop DESTINATION /usr/share/fragview/ )

# 	ENDIF()

# 	# Install samples.
# 	#TODO resolve install path
# 	# INSTALL( FILES ${SAMPLE_GLSL_FILES} DESTINATION /usr/share/fragview/samples/glsl COMPONENT ${BINFRAGVIEW_COMPONENT})
# 	# INSTALL( FILES ${SAMPLE_HLSL_FILES} DESTINATION /usr/share/fragview/samples/hlsl COMPONENT ${BINFRAGVIEW_COMPONENT})
# 	# INSTALL( FILES ${SAMPLE_SPIRV_FILES} DESTINATION /usr/share/fragview/samples/spriv COMPONENT ${BINFRAGVIEW_COMPONENT})
# 	# INSTALL( FILES ${SAMPLE_CLC_FILES} DESTINATION /usr/share/fragview/samples/clc COMPONENT ${BINFRAGVIEW_COMPONENT})
# ENDIF()