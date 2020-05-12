set (VUL_TESTS_NAME vul_tests)
file(GLOB_RECURSE SRC_FILES *.cpp)

add_executable(${VUL_TESTS_NAME} ${SRC_FILES})
set_target_properties(${VUL_TESTS_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${VUL_TESTS_NAME} PRIVATE cxx_std_20)
target_link_libraries(${VUL_TESTS_NAME} PRIVATE ${VUL_PROJECT_NAME})
target_include_directories(${VUL_TESTS_NAME} PRIVATE ./)
