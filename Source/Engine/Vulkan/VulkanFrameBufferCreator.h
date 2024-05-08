//
// Created by erik on 08.05.24.
//

#ifndef VULKANFRAMEBUFFERCREATOR_H
#define VULKANFRAMEBUFFERCREATOR_H

namespace vk {
    class Device;
    class ImageView;
    class RenderPass;
    class Framebuffer;
    struct Extent2D;
}

class VulkanFrameBufferCreator {

public:

    static std::vector<vk::Framebuffer> Create(const vk::Device& device, const std::vector<vk::ImageView>& swapchainImageViews, const vk::RenderPass& renderPass, const vk::Extent2D& swapchainExtent);

};



#endif //VULKANFRAMEBUFFERCREATOR_H
