//
// Created by erik on 03.05.24.
//

#ifndef VULKANCONTEXT_H
#define VULKANCONTEXT_H

#include "Window.h"

namespace vk {
    class Instance;
    class PhysicalDevice;
    class Device;
    class Queue;
    class SurfaceKHR;
}

struct VulkanQueue {
    mutable uint32 familyIndex;
    mutable vk::Queue* queue;
};

class VulkanContext {

public:
    VulkanContext(Window& window);
    ~VulkanContext();

private:
    std::vector<const char*> requiredExtensions;
    std::vector<const char*> requiredLayers;

    [[nodiscard]] vk::Instance* createInstance() const;
    [[nodiscard]] vk::PhysicalDevice* selectPhysicalDevice() const;
    [[nodiscard]] vk::Device* createLogicalDevice() const;
    [[nodiscard]] vk::Queue* getGraphicsQueue(uint32 familyIndex) const;
    [[nodiscard]] vk::SurfaceKHR* createSurface() const;

    vk::Instance* instance;
    vk::PhysicalDevice* physicalDevice;
    vk::Device* logicalDevice;
    vk::SurfaceKHR* surface;

    VulkanQueue graphicsQueue;

};



#endif //VULKANCONTEXT_H
