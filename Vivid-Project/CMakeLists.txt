cmake_minimum_required (VERSION 3.8)
project (VividProject  LANGUAGES C CXX VERSION 0.0.1 DESCRIPTION "The Vivid Engine Project")

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
add_subdirectory(Libs/glfw)
add_subdirectory(VividCore)
add_subdirectory(VividTests)
add_subdirectory(VividGame)
