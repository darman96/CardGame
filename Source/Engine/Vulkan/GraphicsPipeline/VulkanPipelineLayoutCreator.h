//
// Created by erik on 08.05.24.
//

#ifndef VULKANPIPELINELAYOUTCREATOR_H
#define VULKANPIPELINELAYOUTCREATOR_H


namespace vk {
    class Device;
    class PipelineLayout;
}

class VulkanPipelineLayoutCreator {

public:

    static vk::PipelineLayout Create(const vk::Device& device);

};



#endif //VULKANPIPELINELAYOUTCREATOR_H
