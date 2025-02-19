#include <memory>

#include "Window.h"
#include "Vulkan/Structs/VulkanContext.h"

class Application {

public:
    Application();

    void Run() const;

private:

    Window AppWindow;
    VulkanContext VkContext;

    // Vulkan command buffers, fences, and semaphores
    std::vector<vk::CommandBuffer> CommandBuffers;
    vk::Fence RenderFence;
    vk::Semaphore ImageAvailableSemaphore;
    vk::Semaphore RenderFinishedSemaphore;
};
