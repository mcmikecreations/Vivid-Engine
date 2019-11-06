file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES inc/*.h)
file(GLOB_RECURSE INP_FILES inc_private/*.h)

add_executable(VividTests ${SRC_FILES})
set_target_properties(VividCore PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(VividTests PRIVATE VividCore)
target_include_directories(VividTests PRIVATE inc)

target_compile_features(VividTests PUBLIC cxx_std_17)