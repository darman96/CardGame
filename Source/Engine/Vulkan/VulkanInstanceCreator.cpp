//
// Created by erik on 05.05.24.
//

#include "VulkanInstanceCreator.h"

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include "Structs/VulkanContext.h"
#include "VulkanExtensionVerifier.h"
#include "VulkanLayerVerifier.h"

vk::Instance VulkanInstanceCreator::Create() {
    const auto appInfo = createApplicationInfo();
    const auto instanceCreateInfo = createInstanceCreateInfo(appInfo);

    return vk::createInstance(instanceCreateInfo);
}

vk::ApplicationInfo VulkanInstanceCreator::createApplicationInfo() {
    return vk::ApplicationInfo {
        .pApplicationName = "Card Game",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "No Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_3
    };
}

vk::InstanceCreateInfo VulkanInstanceCreator::createInstanceCreateInfo(const vk::ApplicationInfo &appInfo) {
    if (!VulkanExtensionVerifier::VerifyInstanceExtensions(VulkanContext::InstanceExtensions))
        throw std::runtime_error("One or more required instance extensions not found!");
    if (!VulkanLayerVerifier::Verify(VulkanContext::ValidationLayers))
        throw std::runtime_error("One or more required validation layers not found!");

    return vk::InstanceCreateInfo {
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = static_cast<uint32_t>(VulkanContext::InstanceExtensions.size()),
        .ppEnabledExtensionNames = VulkanContext::InstanceExtensions.data(),
        .enabledLayerCount = static_cast<uint32_t>(VulkanContext::ValidationLayers.size()),
        .ppEnabledLayerNames = VulkanContext::ValidationLayers.data()
    };
}
