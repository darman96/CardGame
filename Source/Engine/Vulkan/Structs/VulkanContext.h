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

    // Vulkan command buffers, fences, and semaphores
    std::vector<vk::CommandBuffer> CommandBuffers;
    vk::Fence RenderFence;
    vk::Semaphore ImageAvailableSemaphore;
    vk::Semaphore RenderFinishedSemaphore;

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
