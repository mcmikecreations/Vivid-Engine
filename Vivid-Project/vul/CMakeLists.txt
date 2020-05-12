set (VUL_PROJECT_NAME vul)
cmake_minimum_required (VERSION 3.8)
project (${VUL_PROJECT_NAME} LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "Vivid Utility Library")

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES inc/*.h)
set(INC_FOLDERS_PUBLIC inc)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(${VUL_PROJECT_NAME} ${SRC_FILES})
# Set language and version
set_target_properties(${VUL_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
# All users of this library will need at least C++20
target_compile_features(${VUL_PROJECT_NAME} PRIVATE cxx_std_20)
# set_property(TARGET ${VUL_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_include_directories(${VUL_PROJECT_NAME} PUBLIC ${INC_FOLDERS_PUBLIC})

# Remove exceptions from the build
if (MSVC)
	target_compile_options(${VUL_PROJECT_NAME} PRIVATE /EHsc)
else()
	target_compile_options(${VUL_PROJECT_NAME} PRIVATE -fno-exceptions)
endif()

option(VUL_BUILD_TESTS "Build tests" ON)
if (VUL_BUILD_TESTS)
	add_subdirectory(tests)
endif (VUL_BUILD_TESTS)
