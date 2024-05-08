//
// Created by erik on 05.05.24.
//

#ifndef VULKANPHYSICALDEVICESELECTOR_H
#define VULKANPHYSICALDEVICESELECTOR_H

namespace vk {
    class Instance;
    class SurfaceKHR;
    class PhysicalDevice;
}

class VulkanPhysicalDeviceSelector {

public:
    VulkanPhysicalDeviceSelector() = delete;
    static vk::PhysicalDevice Select(const vk::Instance& instance, const vk::SurfaceKHR& surface);

private:
    static bool isDeviceSuitable(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface);
    static bool isSwapChainSuitable(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface);

};

#endif //VULKANPHYSICALDEVICESELECTOR_H
