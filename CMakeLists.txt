cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
project(vulkan_vs)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-autolink")

# glfw的库目录路径
include_directories(/opt/homebrew/include ./include)

link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib)
# Vulkan的库目录
include_directories(/Users/hejian/VulkanSDK/1.3.239.0/macOS/include/)
link_directories(/Users/hejian/VulkanSDK/1.3.239.0/macOS/lib)

set(librariesList
    GLFW
    vulkan
)

add_executable(vulkan_vs
                main.cpp
                trangles.h
                trangles.cpp
              )
                
target_link_libraries(vulkan_vs ${librariesList})
