//
// Created by erik on 05.05.24.
//

#ifndef VULKANSURFACECREATOR_H
#define VULKANSURFACECREATOR_H

namespace vk {
    class Instance;
    class SurfaceKHR;
}

class VulkanSurfaceCreator {

public:
    VulkanSurfaceCreator() = delete;
    static vk::SurfaceKHR Create(const class Window& window, const vk::Instance& instance);

};



#endif //VULKANSURFACECREATOR_H
