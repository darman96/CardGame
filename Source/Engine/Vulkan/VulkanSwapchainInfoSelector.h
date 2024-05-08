//
// Created by erik on 05.05.24.
//

#ifndef VULKANSWAPCHAININFOSELECTOR_H
#define VULKANSWAPCHAININFOSELECTOR_H

#include "Structs/VulkanSwapchainInfo.h"

namespace vk {
    class SurfaceKHR;
    class PhysicalDevice;
}

class VulkanSwapchainInfoSelector {

public:
    VulkanSwapchainInfoSelector() = delete;
    static VulkanSwapchainInfo Select(const vk::PhysicalDevice& physicalDevice, const vk::SurfaceKHR& surface);

};



#endif //VULKANSWAPCHAININFOSELECTOR_H
