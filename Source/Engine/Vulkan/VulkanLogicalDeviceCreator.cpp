//
// Created by erik on 05.05.24.
//

#include "VulkanLogicalDeviceCreator.h"

#include <set>
#include <vulkan/vulkan.hpp>

#include "Structs/VulkanContext.h"
#include "VulkanQueueFamilySelector.h"


vk::Device VulkanLogicalDeviceCreator::Create(const vk::PhysicalDevice &physicalDevice, const VulkanQueueFamilyInfo& queueFamilyInfo) {
    const auto queueCreateInfos = createQueueCreateInfos(queueFamilyInfo);

    constexpr auto deviceFeatures = vk::PhysicalDeviceFeatures {};
    const auto createInfo = vk::DeviceCreateInfo{
        .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
        .pQueueCreateInfos = queueCreateInfos.data(),
        .enabledLayerCount = static_cast<uint32_t>(VulkanContext::ValidationLayers.size()),
        .ppEnabledLayerNames = VulkanContext::ValidationLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(VulkanContext::DeviceExtensions.size()),
        .ppEnabledExtensionNames = VulkanContext::DeviceExtensions.data(),
        .pEnabledFeatures = &deviceFeatures,
    };

    return physicalDevice.createDevice(createInfo);
}

std::vector<vk::DeviceQueueCreateInfo> VulkanLogicalDeviceCreator::createQueueCreateInfos(const VulkanQueueFamilyInfo& queueFamilyInfo) {
    const std::set uniqueIndices = {
        queueFamilyInfo.GraphicsFamilyIndex.value(),
        queueFamilyInfo.PresentFamilyIndex.value()
    };
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos(uniqueIndices.size());

    constexpr float queuePriority = 1.0f;
    for (const auto index : uniqueIndices) {
        queueCreateInfos[index] = vk::DeviceQueueCreateInfo{
            .queueFamilyIndex = index,
            .queueCount = 1,
            .pQueuePriorities = &queuePriority
        };
    }

    return queueCreateInfos;
}
