cmake_minimum_required(VERSION 3.10)

project(vulkan_vs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-autolink")
#set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install")
#message("CMAKE_INSTALL_PREFIX：" ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "" FORCE)

# Set compiler and linker flags based on platform
if (UNIX)
    set(CMAKE_C_COMPILER "/usr/bin/clang")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

# glfw and Vulkan library directories
if (UNIX)
    include_directories(/opt/homebrew/include ./include)
    link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib)

    include_directories(/Users/hejian/VulkanSDK/1.3.239.0/macOS/include/)
    link_directories(/Users/hejian/VulkanSDK/1.3.243.0/macOS/lib)

    include_directories(/Users/hejian/10_OpenLib/stb)

    # Libraries to link against
    set(librariesList
        GLFW
        vulkan
    )
elseif (WIN32)
    include_directories(E:/OpenSourceLib/glfw-3.3.8.bin.WIN64/include)
    link_directories(E:/OpenSourceLib/glfw-3.3.8.bin.WIN64/lib-vc2022)

    include_directories(C:/VulkanSDK/1.3.231.1/Include)
    link_directories(C:/VulkanSDK/1.3.231.1/Lib)

    # Libraries to link against
    set(librariesList
        glfw3.lib
        vulkan-1.lib
    )
endif()

add_executable(vulkan_vs
    main.cpp
    trangles.h
    trangles.cpp
)

target_link_libraries(vulkan_vs ${librariesList})
