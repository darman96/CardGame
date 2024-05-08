//
// Created by erik on 05.05.24.
//

#include "VulkanPhysicalDeviceSelector.h"

#include <vulkan/vulkan.hpp>

#include "Structs/VulkanContext.h"
#include "VulkanExtensionVerifier.h"
#include "VulkanQueueFamilySelector.h"
#include "VulkanSwapchainInfoSelector.h"

vk::PhysicalDevice VulkanPhysicalDeviceSelector::Select(const vk::Instance& instance, const vk::SurfaceKHR& surface) {
    std::cout << "Selecting physical device" << std::endl;
    std::cout << "Available physical devices:" << std::endl;

    const auto availableDevices = instance.enumeratePhysicalDevices();
    if (availableDevices.empty())
        throw std::runtime_error("No Vulkan devices found");

    std::vector<vk::PhysicalDevice> suitableDevices;
    for (const auto device: availableDevices) {
        const auto properties = device.getProperties();
        std::cout << "\t" << properties.deviceName << ": " << to_string(properties.deviceType) << std::endl;
        if (isDeviceSuitable(device, surface)) {
            suitableDevices.push_back(device);
        }
    }

    return suitableDevices[0];
}

bool VulkanPhysicalDeviceSelector::isDeviceSuitable(const vk::PhysicalDevice &device, const vk::SurfaceKHR &surface) {
    if (!VulkanExtensionVerifier::VerifyDeviceExtensions(device, VulkanContext::DeviceExtensions))
        return false;

    if (const auto queueFamilyInfo = VulkanQueueFamilySelector::Select(device, surface);
        !queueFamilyInfo.IsComplete()) {
        return false;
    }

    if (!isSwapChainSuitable(device, surface))
        return false;

    return true;
}

bool VulkanPhysicalDeviceSelector::isSwapChainSuitable(const vk::PhysicalDevice &device, const vk::SurfaceKHR &surface) {
    const auto swapchainInfo = VulkanSwapchainInfoSelector::Select(device, surface);
    if (swapchainInfo.surfaceFormats.empty())
        return false;

    if (swapchainInfo.presentModes.empty())
        return false;

    return true;
}