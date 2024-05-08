//
// Created by erik on 05.05.24.
//

#include "VulkanContextCreator.h"

#include "VulkanFrameBufferCreator.h"
#include "VulkanImageViewCreator.h"
#include "Structs/VulkanContext.h"
#include "VulkanInstanceCreator.h"
#include "VulkanLogicalDeviceCreator.h"
#include "VulkanPhysicalDeviceSelector.h"
#include "VulkanQueueFamilySelector.h"
#include "VulkanSurfaceCreator.h"
#include "VulkanSwapchainCreator.h"
#include "GraphicsPipeline/VulkanGraphicsPipelineCreator.h"

VulkanContext VulkanContextCreator::Create(const Window& window) {
    const auto instance = VulkanInstanceCreator::Create();
    const auto surface = VulkanSurfaceCreator::Create(window, instance);
    const auto physicalDevice = VulkanPhysicalDeviceSelector::Select(instance, surface);
    const auto queueFamilyInfo = VulkanQueueFamilySelector::Select(physicalDevice, surface);
    const auto logicalDevice = VulkanLogicalDeviceCreator::Create(physicalDevice, queueFamilyInfo);
    const auto graphicsQueue = logicalDevice.getQueue(queueFamilyInfo.GraphicsFamilyIndex.value(), 0);
    const auto presentQueue = logicalDevice.getQueue(queueFamilyInfo.PresentFamilyIndex.value(), 0);
    const auto swapchain = VulkanSwapchainCreator::Create(physicalDevice, logicalDevice, surface, window, queueFamilyInfo);
    const auto swapchainImages = logicalDevice.getSwapchainImagesKHR(std::get<vk::SwapchainKHR>(swapchain));
    const auto swapchainImageViews = VulkanImageViewCreator::Create(logicalDevice, std::get<vk::Format>(swapchain), swapchainImages);
    const auto graphicsPipeline = VulkanGraphicsPipelineCreator::Create(logicalDevice, std::get<vk::Extent2D>(swapchain));
    const auto swapchainFramebuffers = VulkanFrameBufferCreator::Create(logicalDevice, swapchainImageViews, graphicsPipeline.RenderPass, std::get<vk::Extent2D>(swapchain));

    return VulkanContext {
        .Instance = instance,
        .Surface = surface,
        .PhysicalDevice = physicalDevice,
        .LogicalDevice = logicalDevice,
        .GraphicsQueue = graphicsQueue,
        .PresentQueue = presentQueue,
        .Swapchain = std::get<vk::SwapchainKHR>(swapchain),
        .SwapchainImageFormat = std::get<vk::Format>(swapchain),
        .SwapchainExtent = std::get<vk::Extent2D>(swapchain),
        .SwapchainImages = swapchainImages,
        .SwapchainImageViews = swapchainImageViews,
        .SwapchainFramebuffers = swapchainFramebuffers,
        .GraphicsPipeline = graphicsPipeline
    };
}
