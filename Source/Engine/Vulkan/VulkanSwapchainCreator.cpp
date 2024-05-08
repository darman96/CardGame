//
// Created by erik on 05.05.24.
//

#include "VulkanSwapchainCreator.h"

#include <vulkan/vulkan.hpp>
#include "VulkanSwapchainInfoSelector.h"
#include "Engine/Window.h"
#include "Structs/VulkanQueueFamilyInfo.h"

std::tuple<vk::SwapchainKHR, vk::Format, vk::Extent2D> VulkanSwapchainCreator::Create(const vk::PhysicalDevice& physicalDevice, const vk::Device& logicalDevice, const vk::SurfaceKHR& surface, const Window& window, const VulkanQueueFamilyInfo& queueFamilyInfo) {
    std::cout << "Creating swapchain" << std::endl;
    const auto swapchainInfo = VulkanSwapchainInfoSelector::Select(physicalDevice, surface);

    const auto surfaceFormat = selectSurfaceFormat(swapchainInfo.surfaceFormats);
    const auto presentMode = selectPresentMode(swapchainInfo.presentModes);
    const auto extent = selectExtent(swapchainInfo.surfaceCapabilities, window);

    auto imageCount = swapchainInfo.surfaceCapabilities.minImageCount + 1;
    if (swapchainInfo.surfaceCapabilities.maxImageCount > 0 && imageCount > swapchainInfo.surfaceCapabilities.maxImageCount) {
        imageCount = swapchainInfo.surfaceCapabilities.maxImageCount;
    }

    auto createInfo = vk::SwapchainCreateInfoKHR {
        .surface = surface,
        .minImageCount = imageCount,
        .imageFormat = surfaceFormat.format,
        .imageColorSpace = surfaceFormat.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
        .imageSharingMode = vk::SharingMode::eExclusive,
        .preTransform = swapchainInfo.surfaceCapabilities.currentTransform,
        .compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque,
        .presentMode = presentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = nullptr
    };

    if (queueFamilyInfo.GraphicsFamilyIndex != queueFamilyInfo.PresentFamilyIndex) {
        createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = (uint32[]){queueFamilyInfo.GraphicsFamilyIndex.value(), queueFamilyInfo.PresentFamilyIndex.value()};
    }

    return {logicalDevice.createSwapchainKHR(createInfo), surfaceFormat.format, extent};
}

vk::SurfaceFormatKHR VulkanSwapchainCreator::selectSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &availableFormats) {
    for (const auto& format: availableFormats) {
        if (format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eVkColorspaceSrgbNonlinear) {
            return format;
        }
    }

    return availableFormats[0];
}

vk::PresentModeKHR VulkanSwapchainCreator::selectPresentMode(const std::vector<vk::PresentModeKHR> &availablePresentModes) {
    for (const auto& presentMode: availablePresentModes) {
        if (presentMode == vk::PresentModeKHR::eMailbox) {
            return presentMode;
        }
    }

    return vk::PresentModeKHR::eFifo;
}

vk::Extent2D VulkanSwapchainCreator::selectExtent(const vk::SurfaceCapabilitiesKHR &capabilities, const Window& window) {
    if (capabilities.currentExtent.width != UINT32_MAX) {
        return capabilities.currentExtent;
    }

    const auto framebuffer = window.GetFramebufferSize();
    return vk::Extent2D {
        .width = std::clamp(std::get<0>(framebuffer), capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
        .height = std::clamp(std::get<1>(framebuffer), capabilities.minImageExtent.height, capabilities.maxImageExtent.height)
    };
}
