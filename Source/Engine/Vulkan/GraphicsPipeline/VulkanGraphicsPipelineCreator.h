//
// Created by erik on 05.05.24.
//

#ifndef VULKANGRAPHICSPIPELINECREATOR_H
#define VULKANGRAPHICSPIPELINECREATOR_H

#include "Structs/VulkanGraphicsPipeline.h"

namespace vk {
    struct Extent2D;
    class Device;
    class ShaderModule;
    class Pipeline;
}

class VulkanGraphicsPipelineCreator {

public:

    static VulkanGraphicsPipeline Create(const vk::Device& device, const vk::Extent2D& extent);

};



#endif //VULKANGRAPHICSPIPELINECREATOR_H
