//
// Created by erik on 03.05.24.
//

#include "VulkanContext.h"

#include "vulkan/vulkan.hpp"

VulkanContext::VulkanContext(Window& window) {
    requiredExtensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_KHR_wayland_surface"
    };
    requiredLayers = {
        "VK_LAYER_KHRONOS_validation",
    };

    instance = createInstance();
    physicalDevice = selectPhysicalDevice();
    logicalDevice = createLogicalDevice();
    graphicsQueue.queue = getGraphicsQueue(graphicsQueue.familyIndex);
    surface = window.createSurface(instance);
}

VulkanContext::~VulkanContext() {
    logicalDevice->destroy();
    instance->destroySurfaceKHR(*surface);
    instance->destroy();
}

vk::Instance* VulkanContext::createInstance() const {
    const auto appInfo = vk::ApplicationInfo(
        "Card Game",
        1,
        "No Engine",
        1,
        VK_API_VERSION_1_2);

    auto extensions = vk::enumerateInstanceExtensionProperties();

    std::cout << "Available extensions:" << std::endl;
    for (const auto extension: extensions) {
        std::cout << "\t" << extension.extensionName << std::endl;
    }

    for (const auto requiredExtension: requiredExtensions) {
        auto extensionFound = false;
        for (auto extension: extensions) {
            if (strcmp(extension.extensionName, requiredExtension) == 0) {
                extensionFound = true;
                break;
            }
        }

        if (!extensionFound) {
            throw std::runtime_error("Required extension not found: " + std::string(requiredExtension));
        }
    }

    auto layers = vk::enumerateInstanceLayerProperties();

    for (const auto requiredLayer: requiredLayers) {
        auto layerFound = false;
        for (auto layer: layers) {
            if (strcmp(layer.layerName, requiredLayer) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            throw std::runtime_error("Required layer not found: " + std::string(requiredLayer));
        }
    }

    const auto createInfo = vk::InstanceCreateInfo(
        {},
        &appInfo,
        requiredLayers.size(),
        requiredLayers.data(),
        requiredExtensions.size(),
        requiredExtensions.data());

    return new vk::Instance(vk::createInstance(createInfo));
}

vk::PhysicalDevice* VulkanContext::selectPhysicalDevice() const {
    std::cout << "Searching for suitable Vulkan device.." << std::endl;
    auto availableDevices = instance->enumeratePhysicalDevices();
    if (availableDevices.empty()) {
        throw std::runtime_error("No Vulkan devices found");
    }

    vk::PhysicalDevice selectedDevice;
    bool deviceFound = false;
    for (auto device: availableDevices) {
        auto properties = device.getProperties();
        std::cout << "Device: " << properties.deviceName << std::endl;
        std::cout << "\tType:" << to_string(properties.deviceType) << std::endl;

        if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
            selectedDevice = device;
            deviceFound = true;
        }
    }

    if (!deviceFound) {
        throw std::runtime_error("No suitable Vulkan device found");
    }

    return new vk::PhysicalDevice(selectedDevice);
}

vk::Device* VulkanContext::createLogicalDevice() const {
    auto queueFamilies = physicalDevice->getQueueFamilyProperties();

    auto familyIndex = 0;
    for (auto queue: queueFamilies) {
        if (queue.queueFlags & vk::QueueFlagBits::eGraphics) {
            break;
        }
        familyIndex++;
    }

    auto queuePriority =  1.0f;
    auto queueCreateInfo = vk::DeviceQueueCreateInfo(
        {},
        familyIndex,
        1,
        &queuePriority);

    graphicsQueue.familyIndex = familyIndex;

    auto createInfo = vk::DeviceCreateInfo(
        {},
        1,
        &queueCreateInfo,
        0,
        nullptr,
        0,
        nullptr,
        new vk::PhysicalDeviceFeatures());

    return new vk::Device(physicalDevice->createDevice(createInfo));
}

vk::Queue * VulkanContext::getGraphicsQueue(const uint32 familyIndex) const {
    return new vk::Queue(logicalDevice->getQueue(familyIndex, 0));
}

vk::SurfaceKHR * VulkanContext::createSurface() const {
    return nullptr;
}
