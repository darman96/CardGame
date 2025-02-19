cmake_minimum_required(VERSION 3.28)
project(CardGame)

set(CMAKE_CXX_STANDARD 20)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW no docs")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW no install")

add_subdirectory(Dependencies/GLFW)

# Vulkan
add_definitions(-DVULKAN_HPP_NO_CONSTRUCTORS)
find_package(Vulkan REQUIRED)

include_directories(Source)

add_executable(CardGame Source/Main.cpp
        Source/Engine/Application.cpp
        Source/Engine/Application.h
        Source/Engine/Vulkan/Structs/VulkanContext.cpp
        Source/Engine/Vulkan/Structs/VulkanContext.h
        Source/Engine/Window.cpp
        Source/Engine/Window.h
        Source/Common.h
        Source/StdAfx.cpp
        Source/StdAfx.h
        Source/Engine/Vulkan/VulkanInstanceCreator.cpp
        Source/Engine/Vulkan/VulkanInstanceCreator.h
        Source/Engine/Vulkan/VulkanExtensionVerifier.cpp
        Source/Engine/Vulkan/VulkanExtensionVerifier.h
        Source/Engine/Vulkan/VulkanContextCreator.cpp
        Source/Engine/Vulkan/VulkanContextCreator.h
        Source/Engine/Vulkan/VulkanPhysicalDeviceSelector.cpp
        Source/Engine/Vulkan/VulkanPhysicalDeviceSelector.h
        Source/Engine/Vulkan/VulkanLayerVerifier.cpp
        Source/Engine/Vulkan/VulkanLayerVerifier.h
        Source/Engine/Vulkan/VulkanSurfaceCreator.cpp
        Source/Engine/Vulkan/VulkanSurfaceCreator.h
        Source/Engine/Vulkan/VulkanLogicalDeviceCreator.cpp
        Source/Engine/Vulkan/VulkanLogicalDeviceCreator.h
        Source/Engine/Vulkan/VulkanQueueFamilySelector.cpp
        Source/Engine/Vulkan/VulkanQueueFamilySelector.h
        Source/Engine/Vulkan/VulkanSwapchainCreator.cpp
        Source/Engine/Vulkan/VulkanSwapchainCreator.h
        Source/Engine/Vulkan/Structs/VulkanSwapchainInfo.h
        Source/Engine/Vulkan/VulkanSwapchainInfoSelector.cpp
        Source/Engine/Vulkan/VulkanSwapchainInfoSelector.h
        Source/Engine/Vulkan/Structs/VulkanQueueFamilyInfo.h
        Source/Engine/Vulkan/VulkanImageViewCreator.cpp
        Source/Engine/Vulkan/VulkanImageViewCreator.h
        Source/Engine/Vulkan/GraphicsPipeline/VulkanGraphicsPipelineCreator.cpp
        Source/Engine/Vulkan/GraphicsPipeline/VulkanGraphicsPipelineCreator.h
        Source/Engine/Vulkan/GraphicsPipeline/Structs/VulkanGraphicsPipeline.h
        Source/Engine/Vulkan/GraphicsPipeline/Structs/VulkanShaderStage.h
        Source/Engine/Vulkan/GraphicsPipeline/VulkanShaderStageCreator.cpp
        Source/Engine/Vulkan/GraphicsPipeline/VulkanShaderStageCreator.h
        Source/Engine/Vulkan/VulkanFrameBufferCreator.cpp
        Source/Engine/Vulkan/VulkanFrameBufferCreator.h
)

# Precompiled headers
target_precompile_headers(CardGame PRIVATE Source/StdAfx.h)

# Linking
target_link_libraries(CardGame glfw Vulkan::Vulkan)
