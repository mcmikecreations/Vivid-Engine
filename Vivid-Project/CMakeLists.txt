cmake_minimum_required (VERSION 3.8)
project (VividProject LANGUAGES C CXX VERSION 0.0.1 DESCRIPTION "A cross-platform multithreaded game engine")

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/Libs/modules")
set(GLM_ROOT_DIR "Libs/glm")
find_package(GLM REQUIRED)
find_package(Vulkan REQUIRED)

include_directories(VividCore/inc)
add_subdirectory(Libs/spdlog)
add_subdirectory(Libs/glfw)
add_subdirectory(Libs/di)

add_subdirectory(VividCore)
add_subdirectory(VividTests)
add_subdirectory(VividGame)

option(BUILD_DOC "Build documentation" ON)
if (BUILD_DOC)
	find_package(Doxygen)
	if (DOXYGEN_FOUND)
		#set(JAVADOC_AUTOBRIEF YES)
		set(EXTRACT_ALL YES)
		set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/docs)
		doxygen_add_docs(documentation
			${PROJECT_SOURCE_DIR}/VividCore)
	else (DOXYGEN_FOUND)
	  message("Doxygen need to be installed to generate the doxygen documentation")
	endif (DOXYGEN_FOUND)
endif (BUILD_DOC)