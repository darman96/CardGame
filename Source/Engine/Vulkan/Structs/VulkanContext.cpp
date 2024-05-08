//
// Created by erik on 03.05.24.
//

#include "VulkanContext.h"

const std::vector<const char*> VulkanContext::InstanceExtensions = {
    VK_KHR_SURFACE_EXTENSION_NAME,
    "VK_KHR_wayland_surface"
};

const std::vector<const char*> VulkanContext::DeviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const std::vector<const char*> VulkanContext::ValidationLayers = {
    "VK_LAYER_KHRONOS_validation",
};

