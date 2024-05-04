//
// Created by erik on 03.05.24.
//

#ifndef VULKANCONTEXT_H
#define VULKANCONTEXT_H

#include <memory>

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
    VulkanContext();
    ~VulkanContext();

    void CreateSurface(class Window* window);

private:
    std::vector<const char*> requiredInstanceExtensions;
    std::vector<const char*> requiredDeviceExtensions;
    std::vector<const char*> requiredLayers;

    [[nodiscard]] vk::Instance* createInstance() const;
    [[nodiscard]] vk::PhysicalDevice* selectPhysicalDevice() const;
    [[nodiscard]] vk::Device* createLogicalDevice() const;
    [[nodiscard]] vk::Queue* getGraphicsQueue(uint32 familyIndex) const;

    vk::Instance* instance;
    vk::PhysicalDevice* physicalDevice;
    vk::Device* logicalDevice;
    vk::SurfaceKHR* surface;

    VulkanQueue graphicsQueue;

};



#endif //VULKANCONTEXT_H
