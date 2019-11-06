file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES inc/*.h)

add_executable(VividGame ${SRC_FILES})
set_target_properties(VividCore PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(VividGame PRIVATE glfw)
target_link_libraries(VividGame PRIVATE VividCore)

target_compile_definitions(VividGame PRIVATE VK_USE_PLATFORM_WIN32_KHR)
target_include_directories(VividGame PRIVATE Vulkan::Vulkan)
target_link_libraries(VividGame PRIVATE Vulkan::Vulkan)

target_compile_features(VividGame PUBLIC cxx_std_17)