//
// Created by erik on 05.05.24.
//

#ifndef VULKANSWAPCHAININFO_H
#define VULKANSWAPCHAININFO_H

#include <vulkan/vulkan.hpp>

struct VulkanSwapchainInfo {

    std::vector<vk::SurfaceFormatKHR> surfaceFormats;
    std::vector<vk::PresentModeKHR> presentModes;
    vk::SurfaceCapabilitiesKHR surfaceCapabilities;

};

#endif //VULKANSWAPCHAININFO_H
