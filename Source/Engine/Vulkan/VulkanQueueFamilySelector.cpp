//
// Created by erik on 05.05.24.
//

#include "VulkanQueueFamilySelector.h"

#include <vulkan/vulkan.hpp>

VulkanQueueFamilyInfo VulkanQueueFamilySelector::Select(const vk::PhysicalDevice &physicalDevice,
    const vk::SurfaceKHR &surface) {
    VulkanQueueFamilyInfo queueFamilyInfo;

    const auto queueFamilies = physicalDevice.getQueueFamilyProperties();

    uint32 i = 0;
    for (const auto& queueFamily: queueFamilies) {
        if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
            queueFamilyInfo.GraphicsFamilyIndex = i;

        if (physicalDevice.getSurfaceSupportKHR(i, surface))
            queueFamilyInfo.PresentFamilyIndex = i;

        if (queueFamilyInfo.IsComplete())
            break;

        i++;
    }

    return queueFamilyInfo;
}
