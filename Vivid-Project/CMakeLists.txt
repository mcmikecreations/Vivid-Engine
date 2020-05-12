cmake_minimum_required (VERSION 3.8)
project (VividProject LANGUAGES C CXX VERSION 0.0.1 DESCRIPTION "A cross-platform multithreaded game engine")

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/Libs/modules")
add_subdirectory(vul)

option(VIVID_BUILD_SOURCE "Build the engine" OFF)
if (VIVID_BUILD_SOURCE)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

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
endif (VIVID_BUILD_SOURCE)

option(VIVID_BUILD_DOC "Build documentation" ON)
if (VIVID_BUILD_DOC)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Vivid-Docs ${CMAKE_CURRENT_BINARY_DIR}/docs)
endif (VIVID_BUILD_DOC)