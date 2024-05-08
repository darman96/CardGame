//
// Created by erik on 05.05.24.
//

#include "VulkanSwapchainInfoSelector.h"
#include <vulkan/vulkan.hpp>

VulkanSwapchainInfo VulkanSwapchainInfoSelector::Select(const vk::PhysicalDevice &physicalDevice, const vk::SurfaceKHR &surface) {
    return VulkanSwapchainInfo {
        .surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface),
        .presentModes = physicalDevice.getSurfacePresentModesKHR(surface),
        .surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface)
    };
}
