file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES inc/*.h)
file(GLOB_RECURSE INP_FILES inc_private/*.h)
set(INC_FOLDERS_PUBLIC inc)
set(INC_FOLDERS_PRIVATE inc_private)

set(ApiChain "glfw_vulkan" CACHE STRING
  "The chain of APIs used by the engine")
set(API_CHAIN_DEFINES "")

set_property(CACHE ApiChain PROPERTY STRINGS glfw_vulkan)

if(ApiChain STREQUAL "glfw_vulkan")
	file(GLOB_RECURSE GLFW_VULKAN_FILES platform/windows/*.cpp)
	list(APPEND SRC_FILES ${GLFW_VULKAN_FILES})
	list(APPEND INC_FOLDERS_PRIVATE platform/windows)

	list(APPEND API_CHAIN_DEFINES VV_GLFW)
	list(APPEND API_CHAIN_DEFINES VV_VULKAN)
endif()
message("Api chain defines were set to " "${API_CHAIN_DEFINES}")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(VividCore ${SRC_FILES}) # ${INC_FILES} ${INP_FILES} 
set_target_properties(VividCore PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(VividCore PUBLIC ${INC_FOLDERS_PUBLIC})
target_include_directories(VividCore PRIVATE ${INC_FOLDERS_PRIVATE})

target_include_directories(VividCore PUBLIC ${GLM_INCLUDE_DIR})
target_link_libraries(VividCore PUBLIC spdlog)

target_compile_definitions(VividCore PUBLIC VK_USE_PLATFORM_WIN32_KHR)
target_include_directories(VividCore PUBLIC Vulkan::Vulkan)
target_link_libraries(VividCore PUBLIC Vulkan::Vulkan)

target_link_libraries(VividCore PUBLIC glfw)
target_link_libraries(VividCore PUBLIC Boost.DI)

# All users of this library will need at least C++17
target_compile_features(VividCore PUBLIC cxx_std_17)
# Remove exceptions from the build
if (MSVC)
	target_compile_options(VividCore PRIVATE /EHsc)
else()
	target_compile_options(VividCore PRIVATE -fno-exceptions)
endif()
# Specify our toolchain, defines which apis we can use
target_compile_definitions(VividCore PRIVATE ${API_CHAIN_DEFINES})
