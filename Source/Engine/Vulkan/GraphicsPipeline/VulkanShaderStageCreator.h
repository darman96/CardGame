//
// Created by erik on 08.05.24.
//

#ifndef VULKANSHADERSTAGECREATOR_H
#define VULKANSHADERSTAGECREATOR_H

namespace vk {
    class Device;
    enum class ShaderStageFlagBits : uint32_t;
}

struct VulkanShaderStage;

class VulkanShaderStageCreator {

public:

    static VulkanShaderStage Create(const vk::Device& device, const std::string& path, vk::ShaderStageFlagBits stage);

private:

    static std::vector<char> readShaderFile(const std::string& filename);
    // static vk::ShaderModule createShaderModule(const vk::Device& device, const std::vector<char>& code);

};



#endif //VULKANSHADERSTAGECREATOR_H
