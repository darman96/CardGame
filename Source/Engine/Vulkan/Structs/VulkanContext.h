//
// Created by erik on 03.05.24.
//

#ifndef VULKANCONTEXT_H
#define VULKANCONTEXT_H

#include <vulkan/vulkan.hpp>

#include "Engine/Vulkan/GraphicsPipeline/Structs/VulkanGraphicsPipeline.h"

struct VulkanContext {

    static const std::vector<const char*> InstanceExtensions;
    static const std::vector<const char*> DeviceExtensions;
    static const std::vector<const char*> ValidationLayers;

    vk::Instance Instance;
    vk::SurfaceKHR Surface;
    vk::PhysicalDevice PhysicalDevice;
    vk::Device LogicalDevice;
    vk::Queue GraphicsQueue;
    vk::Queue PresentQueue;
    vk::SwapchainKHR Swapchain;
    vk::Format SwapchainImageFormat;
    vk::Extent2D SwapchainExtent;
    std::vector<vk::Image> SwapchainImages;
    std::vector<vk::ImageView> SwapchainImageViews;
    std::vector<vk::Framebuffer> SwapchainFramebuffers;

    VulkanGraphicsPipeline GraphicsPipeline;

    ~VulkanContext() {
        LogicalDevice.waitIdle();
        for (const auto& framebuffer : SwapchainFramebuffers) {
            LogicalDevice.destroyFramebuffer(framebuffer);
        }
        for (const auto& imageView : SwapchainImageViews) {
            LogicalDevice.destroyImageView(imageView);
        }
        LogicalDevice.destroySwapchainKHR(Swapchain);
        LogicalDevice.destroy();
        Instance.destroySurfaceKHR(Surface);
        Instance.destroy();
    }

};

#endif //VULKANCONTEXT_H
