cmake_minimum_required(VERSION 3.10)
project(Vulkan-Playground)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan 1.4.335 REQUIRED)
find_package(slang CONFIG HINTS "$ENV{VULKAN_SDK}/lib/cmake")
find_program(SLANGC_EXECUTABLE slangc HINTS "$ENV{VULKAN_SDK}/bin" REQUIRED)
add_subdirectory(external/glfw)

add_executable(${PROJECT_NAME} Source/main.cpp)


target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

function (add_slang_shader_target TARGET)
  cmake_parse_arguments ("SHADER" "" "" "SOURCES" ${ARGN})
  set (SHADERS_DIR ${CMAKE_CURRENT_LIST_DIR}/Shaders)
  set (ENTRY_POINTS -entry vertMain -entry fragMain)
  add_custom_command (
          OUTPUT ${SHADERS_DIR}
          COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADERS_DIR}
  )
  add_custom_command (
          OUTPUT  ${SHADERS_DIR}/slang.spv
          COMMAND ${SLANGC_EXECUTABLE} ${SHADER_SOURCES} -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name ${ENTRY_POINTS} -o slang.spv
          WORKING_DIRECTORY ${SHADERS_DIR}
          DEPENDS ${SHADERS_DIR} ${SHADER_SOURCES}
          COMMENT "Compiling Slang Shaders"
          VERBATIM
  )
  add_custom_target (${TARGET} DEPENDS ${SHADERS_DIR}/slang.spv)
endfunction()

set (SHADER_SLANG_TARGET ${PROJECT_NAME}_slang_shader)

add_slang_shader_target(${SHADER_SLANG_TARGET}
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/Shaders/shader.slang
)

add_dependencies(${PROJECT_NAME} ${SHADER_SLANG_TARGET})

target_compile_definitions(${PROJECT_NAME} PRIVATE SHADERS_DIR="${CMAKE_CURRENT_LIST_DIR}/Shaders")
