
FIND_PACKAGE(GTest REQUIRED)
IF(GTEST_FOUND)
	MESSAGE(STATUS "Gtest found: ${GTEST_BOTH_LIBRARIES}")
ELSE()
	MESSAGE(ERROR "Gtest is required in order to compile and run the tests")
ENDIF()


# Get the include directories for the target.
get_target_property(LIBVDENGINE_INCLUDES vdengine INCLUDE_DIRECTORIES)

# Source files.
FILE(GLOB SOURCE_FILES 	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

ADD_EXECUTABLE(vdengine-assert ${SOURCE_FILES} ${HEADER_FILES})
TARGET_LINK_LIBRARIES(vdengine-assert ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} vdengine )
TARGET_INCLUDE_DIRECTORIES(vdengine-assert PRIVATE ${GTEST_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${LIBVDENGINE_INCLUDES})
ADD_DEPENDENCIES(vdengine-assert vdengine)

INSTALL(TARGETS vdengine-assert DESTINATION bin)
ADD_TEST(NAME assert-functionality
		COMMAND vdengine-assert
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
