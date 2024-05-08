//
// Created by erik on 08.05.24.
//

#include "VulkanShaderStageCreator.h"

#include <fstream>

#include "Structs/VulkanShaderStage.h"

VulkanShaderStage VulkanShaderStageCreator::Create(const vk::Device &device, const std::string &path, vk::ShaderStageFlagBits stage) {
    const auto shaderCode = readShaderFile(path);

    const auto createInfo = vk::ShaderModuleCreateInfo {
        .codeSize = shaderCode.size(),
        .pCode = reinterpret_cast<const uint32_t *>(shaderCode.data())
    };

    const auto shaderModule = device.createShaderModule(createInfo);

    return VulkanShaderStage {
        .CreateInfo = vk::PipelineShaderStageCreateInfo {
            .stage = stage,
            .module = shaderModule,
            .pName = "main"
        },
        .ShaderModule = shaderModule,
        .Device = device
    };
}

std::vector<char> VulkanShaderStageCreator::readShaderFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
        throw std::runtime_error("Failed to open file!");

    const auto fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}
