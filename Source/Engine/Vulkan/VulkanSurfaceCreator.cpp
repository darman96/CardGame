//
// Created by erik on 05.05.24.
//

#include "VulkanSurfaceCreator.h"

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include "Engine/Window.h"

vk::SurfaceKHR VulkanSurfaceCreator::Create(const Window &window, const vk::Instance &instance) {
    vk::SurfaceKHR surface;
    if (glfwCreateWindowSurface(instance, window.window, nullptr, reinterpret_cast<VkSurfaceKHR*>(&surface)) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface!");
    }

    return surface;
}
