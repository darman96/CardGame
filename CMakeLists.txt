cmake_minimum_required(VERSION 3.28)
project(CardGame)

set(CMAKE_CXX_STANDARD 20)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW no docs")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW no install")

add_subdirectory(Dependencies/GLFW)

# Vulkan
set(VULKAN_SDK "Dependencies/VulkanSdk/1.3.280.1/x86_64" CACHE PATH "Vulkan SDK path")
find_package(Vulkan REQUIRED)


add_executable(CardGame Source/Main.cpp
        Source/Application.cpp
        Source/Application.h
        Source/VulkanContext.cpp
        Source/VulkanContext.h
        Source/Window.cpp
        Source/Window.h
        Source/Common.h
        Source/StdAfx.cpp
        Source/StdAfx.h)

# Precompiled headers
target_precompile_headers(CardGame PRIVATE Source/StdAfx.h)

# Linking
target_link_libraries(CardGame glfw Vulkan::Vulkan)
