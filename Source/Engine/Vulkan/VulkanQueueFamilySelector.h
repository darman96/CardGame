//
// Created by erik on 05.05.24.
//

#ifndef VULKANQUEUEFAMILYSELECTOR_H
#define VULKANQUEUEFAMILYSELECTOR_H
#include "Structs/VulkanQueueFamilyInfo.h"

namespace vk {
    class PhysicalDevice;
    class SurfaceKHR;
}

class VulkanQueueFamilySelector {

public:
    VulkanQueueFamilySelector() = delete;
    static VulkanQueueFamilyInfo Select(const vk::PhysicalDevice& physicalDevice, const vk::SurfaceKHR& surface);

};



#endif //VULKANQUEUEFAMILYSELECTOR_H
