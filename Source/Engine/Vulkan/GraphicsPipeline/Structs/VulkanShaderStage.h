//
// Created by erik on 08.05.24.
//

#ifndef VULKANSHADERSTAGE_H
#define VULKANSHADERSTAGE_H

#include <vulkan/vulkan.hpp>

struct VulkanShaderStage {

    vk::PipelineShaderStageCreateInfo CreateInfo;
    vk::ShaderModule ShaderModule;
    const vk::Device& Device;

    ~VulkanShaderStage() {
        Device.destroyShaderModule(ShaderModule);
    }

};



#endif //VULKANSHADERSTAGE_H
