#include "StdAfx.h"
#include "Application.h"

#include "Vulkan/VulkanContextCreator.h"

Application::Application()
    : AppWindow(::Window(WindowProps("Card Game", 800, 600))),
      VkContext(VulkanContextCreator::Create(AppWindow)) {}

void Application::Run() const {

    while (AppWindow.IsOpen()) {
        AppWindow.PollEvents();

        // Record command buffer
        vk::CommandBufferBeginInfo beginInfo{};
        VkContext.CommandBuffers[0].begin(beginInfo);

        vk::RenderPassBeginInfo renderPassInfo{};
        renderPassInfo.renderPass = VkContext.GraphicsPipeline.RenderPass;
        renderPassInfo.framebuffer = VkContext.SwapchainFramebuffers[0];
        renderPassInfo.renderArea.offset = vk::Offset2D{0, 0};
        renderPassInfo.renderArea.extent = VkContext.SwapchainExtent;

        vk::ClearValue clearColor = vk::ClearValue{std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        VkContext.CommandBuffers[0].beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);
        VkContext.CommandBuffers[0].bindPipeline(vk::PipelineBindPoint::eGraphics, VkContext.GraphicsPipeline.Pipeline);
        VkContext.CommandBuffers[0].draw(3, 1, 0, 0);
        VkContext.CommandBuffers[0].endRenderPass();
        VkContext.CommandBuffers[0].end();

        // Submit command buffer
        vk::SubmitInfo submitInfo{};
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &VkContext.CommandBuffers[0];

        VkContext.GraphicsQueue.submit(submitInfo, VkContext.RenderFence);
        VkContext.GraphicsQueue.waitIdle();

        AppWindow.Present();
    }

}
