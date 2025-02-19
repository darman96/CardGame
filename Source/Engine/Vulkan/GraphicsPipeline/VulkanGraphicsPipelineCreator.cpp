#include "VulkanGraphicsPipelineCreator.h"
#include "VulkanShaderStageCreator.h"
#include "Structs/VulkanShaderStage.h"

#include <fstream>
#include <vulkan/vulkan.hpp>


VulkanGraphicsPipeline VulkanGraphicsPipelineCreator::Create(const vk::Device& device, const vk::Extent2D& extent) {
    std::cout << "Creating graphics pipeline" << std::endl;
    const auto vertShaderStage = VulkanShaderStageCreator::Create(
        device,
        "../Shaders/vert.spv",
        vk::ShaderStageFlagBits::eVertex);

    const auto fragShaderStage = VulkanShaderStageCreator::Create(
        device,
        "../Shaders/frag.spv",
        vk::ShaderStageFlagBits::eFragment);

    auto shaderStages = std::array {
        vertShaderStage.CreateInfo,
        fragShaderStage.CreateInfo
    };

    constexpr auto dynamicStates = std::array {
        vk::DynamicState::eViewport,
        vk::DynamicState::eLineWidth,
        vk::DynamicState::eScissor
    };

    auto dynamicState = vk::PipelineDynamicStateCreateInfo {
        .dynamicStateCount = dynamicStates.size(),
        .pDynamicStates = dynamicStates.data(),
    };

    constexpr auto vertexInputInfo = vk::PipelineVertexInputStateCreateInfo {
        .vertexBindingDescriptionCount = 0,
        .vertexAttributeDescriptionCount = 0
    };

    constexpr auto inputAssembly = vk::PipelineInputAssemblyStateCreateInfo {
        .topology = vk::PrimitiveTopology::eTriangleList,
        .primitiveRestartEnable = VK_FALSE
    };

    const auto viewport = vk::Viewport {
        .x = 0.0f,
        .y = 0.0f,
        .width = static_cast<float>(extent.width),
        .height = static_cast<float>(extent.height),
        .minDepth = 0.0f,
        .maxDepth = 1.0f
    };

    const auto scissor = vk::Rect2D {
        .offset = {0, 0},
        .extent = extent
    };

    const auto viewportState = vk::PipelineViewportStateCreateInfo {
        .viewportCount = 1,
        .pViewports = &viewport,
        .scissorCount = 1,
        .pScissors = &scissor
    };

    constexpr auto rasterizer = vk::PipelineRasterizationStateCreateInfo {
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = vk::PolygonMode::eFill,
        .cullMode = vk::CullModeFlagBits::eBack,
        .frontFace = vk::FrontFace::eClockwise,
        .depthBiasEnable = VK_FALSE,
        .lineWidth = 1.0f
    };

    constexpr auto multisampling = vk::PipelineMultisampleStateCreateInfo {
        .rasterizationSamples = vk::SampleCountFlagBits::e1,
        .sampleShadingEnable = VK_FALSE
    };

    const auto colorBlendAttachment = vk::PipelineColorBlendAttachmentState {
        .blendEnable = VK_FALSE,
        .colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA
    };

    const auto colorBlending = vk::PipelineColorBlendStateCreateInfo {
        .logicOpEnable = VK_FALSE,
        .logicOp = vk::LogicOp::eCopy,
        .attachmentCount = 1,
        .pAttachments = &colorBlendAttachment
    };

    constexpr auto pipelineLayoutInfo = vk::PipelineLayoutCreateInfo {
        .setLayoutCount = 0,
        .pushConstantRangeCount = 0
    };

    const auto pipelineLayout = device.createPipelineLayout(pipelineLayoutInfo);

    const auto colorAttachmentDescription = vk::AttachmentDescription {
        .format = vk::Format::eB8G8R8A8Srgb,
        .samples = vk::SampleCountFlagBits::e1,
        .loadOp = vk::AttachmentLoadOp::eClear,
        .storeOp = vk::AttachmentStoreOp::eStore,
        .stencilLoadOp = vk::AttachmentLoadOp::eDontCare,
        .stencilStoreOp = vk::AttachmentStoreOp::eDontCare,
        .initialLayout = vk::ImageLayout::eUndefined,
        .finalLayout = vk::ImageLayout::ePresentSrcKHR
    };

    const auto colorAttachmentRef = vk::AttachmentReference {
        .attachment = 0,
        .layout = vk::ImageLayout::eColorAttachmentOptimal
    };

    const auto subpassDescription = vk::SubpassDescription {
        .pipelineBindPoint = vk::PipelineBindPoint::eGraphics,
        .colorAttachmentCount = 1,
        .pColorAttachments = &colorAttachmentRef
    };

    const auto renderPassInfo = vk::RenderPassCreateInfo {
        .attachmentCount = 1,
        .pAttachments = &colorAttachmentDescription,
        .subpassCount = 1,
        .pSubpasses = &subpassDescription
    };

    const auto renderPass = device.createRenderPass(renderPassInfo);

    const auto createInfo = vk::GraphicsPipelineCreateInfo {
        .stageCount = shaderStages.size(),
        .pStages = shaderStages.data(),
        .pVertexInputState = &vertexInputInfo,
        .pInputAssemblyState = &inputAssembly,
        .pViewportState = &viewportState,
        .pRasterizationState = &rasterizer,
        .pMultisampleState = &multisampling,
        .pDepthStencilState = nullptr,
        .pColorBlendState = &colorBlending,
        .pDynamicState = &dynamicState,
        .layout = pipelineLayout,
        .renderPass = renderPass,
        .subpass = 0,
        .basePipelineHandle = nullptr,
    };

    const auto pipelineResult = device.createGraphicsPipeline(nullptr, createInfo);

    if (pipelineResult.result != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create graphics pipeline!");
    }

    return VulkanGraphicsPipeline {
        .Layout = pipelineLayout,
        .RenderPass = renderPass,
        .Pipeline = pipelineResult.value,
        .Device = device
    };
}
