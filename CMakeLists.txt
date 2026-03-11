cmake_minimum_required(VERSION 3.10)
project(Vulkan-Playground)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan 1.4.335 REQUIRED)
find_package(slang CONFIG HINTS "$ENV{VULKAN_SDK}/lib/cmake")
add_subdirectory(external/glfw)

add_executable(${PROJECT_NAME} Source/main.cpp)


target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
