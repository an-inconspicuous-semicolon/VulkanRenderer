cmake_minimum_required(VERSION 3.12)
project(VulkanRenderer
        VERSION 0.1.0.0
        DESCRIPTION "A Vulkan Renderer"
        HOMEPAGE_URL "https://github.com/an-inconspicuous-semicolon/VulkanRenderer"
        LANGUAGES CXX)
set(PROJECT_SHORT_NAME vulren)

include(CMake/pre_lib.cmake)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} SHARED ${LIBRARY_INCLUDE_PATH}/${PROJECT_NAME}/api.hpp Library/src/VulkanRenderer.cpp Library/include/VulkanRenderer/VulkanRenderer.hpp Library/include/VulkanRenderer/common.hpp Library/include/VulkanRenderer/Utility/Wrapper.hpp)
target_include_directories(${PROJECT_NAME}
        PUBLIC ${LIBRARY_INCLUDE_PATH}
        PRIVATE ${LIBRARY_INCLUDE_PATH}/${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        PRIVATE glfw glm)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${LIBRARY_INCLUDE_PATH}/${PROJECT_NAME}/common.hpp)

include(CMake/post_lib.cmake)
