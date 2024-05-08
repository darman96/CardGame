//
// Created by erik on 05.05.24.
//

#ifndef VULKANLOGICALDEVICECREATOR_H
#define VULKANLOGICALDEVICECREATOR_H

struct VulkanQueueFamilyInfo;

namespace vk {
    class PhysicalDevice;
    class SurfaceKHR;
    class Device;
    struct DeviceQueueCreateInfo;
}

class VulkanLogicalDeviceCreator {

public:

    static vk::Device Create(const vk::PhysicalDevice& physicalDevice, const VulkanQueueFamilyInfo& queueFamilyInfo);

private:

    static std::vector<vk::DeviceQueueCreateInfo> createQueueCreateInfos(const VulkanQueueFamilyInfo& queueFamilyInfo);
};



#endif //VULKANLOGICALDEVICECREATOR_H
