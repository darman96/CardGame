//
// Created by erik on 05.05.24.
//

#ifndef VULKANSWAPCHAINCREATOR_H
#define VULKANSWAPCHAINCREATOR_H

namespace vk {
    class SurfaceKHR;
    class Device;
    class PhysicalDevice;
    class SwapchainKHR;
    struct SurfaceCapabilitiesKHR;
    struct SurfaceFormatKHR;
    struct Extent2D;
    enum class Format;
    enum class PresentModeKHR;
}

class Window;
struct VulkanQueueFamilyInfo;

class VulkanSwapchainCreator {

public:

    static std::tuple<vk::SwapchainKHR, vk::Format, vk::Extent2D> Create(const vk::PhysicalDevice& physicalDevice, const vk::Device& logicalDevice, const vk::SurfaceKHR& surface, const Window& window, const VulkanQueueFamilyInfo& queueFamilyInfo);

private:

    static vk::SurfaceFormatKHR selectSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats);
    static vk::PresentModeKHR selectPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes);
    static vk::Extent2D selectExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const Window& window);

};



#endif //VULKANSWAPCHAINCREATOR_H
