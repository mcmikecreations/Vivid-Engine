file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES inc/*.h)
file(GLOB_RECURSE INP_FILES inc_private/*.h)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(VividCore ${SRC_FILES}) # ${INC_FILES} ${INP_FILES} 
set_target_properties(VividCore PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(VividCore PUBLIC inc)
target_include_directories(VividCore PRIVATE inc_private)

target_include_directories(VividCore PUBLIC ${GLM_INCLUDE_DIR})
target_link_libraries(VividCore PUBLIC spdlog)

target_compile_definitions(VividCore PUBLIC VK_USE_PLATFORM_WIN32_KHR)
target_include_directories(VividCore PUBLIC Vulkan::Vulkan)
target_link_libraries(VividCore PUBLIC Vulkan::Vulkan)

target_link_libraries(VividCore PUBLIC glfw)
target_link_libraries(VividCore PUBLIC Boost.DI)

# All users of this library will need at least C++17
target_compile_features(VividCore PUBLIC cxx_std_17)
target_compile_options(VividCore PRIVATE -fno-exceptions)
target_compile_options(VividCore PRIVATE /EHsc)
