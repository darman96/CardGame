//
// Created by erik on 08.05.24.
//

#include "VulkanFrameBufferCreator.h"

#include <vulkan/vulkan.hpp>

std::vector<vk::Framebuffer> VulkanFrameBufferCreator::Create(const vk::Device& device, const std::vector<vk::ImageView>& swapchainImageViews, const vk::RenderPass& renderPass, const vk::Extent2D& swapchainExtent) {
    std::cout << "Creating framebuffers" << std::endl;
    std::vector<vk::Framebuffer> swapchainFramebuffers(swapchainImageViews.size());

    for (auto i = 0; i < swapchainImageViews.size(); i++) {
        vk::ImageView attachments[] = {
            swapchainImageViews[i]
        };

        auto createInfo = vk::FramebufferCreateInfo {
            .renderPass = renderPass,
            .attachmentCount = 1,
            .pAttachments = attachments,
            .width = swapchainExtent.width,
            .height = swapchainExtent.height,
            .layers = 1
        };

        swapchainFramebuffers[i] = device.createFramebuffer(createInfo);
    }

    return swapchainFramebuffers;
}
