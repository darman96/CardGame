//
// Created by erik on 08.05.24.
//

#ifndef VULKANGRAPHICSPIPELINE_H
#define VULKANGRAPHICSPIPELINE_H

#include <vulkan/vulkan.hpp>

struct VulkanGraphicsPipeline {

    vk::PipelineLayout Layout;
    vk::RenderPass RenderPass;
    vk::Pipeline Pipeline;

    const vk::Device& Device;

    ~VulkanGraphicsPipeline() {
        Device.destroyPipeline(Pipeline);
        Device.destroyPipelineLayout(Layout);
        Device.destroyRenderPass(RenderPass);
    }

};



#endif //VULKANGRAPHICSPIPELINE_H
