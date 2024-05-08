//
// Created by erik on 05.05.24.
//

#ifndef VULKANCONTEXTCREATOR_H
#define VULKANCONTEXTCREATOR_H

struct VulkanContext;

class VulkanContextCreator {

public:

    VulkanContextCreator() = delete;
    static VulkanContext Create(const class Window& window);

};



#endif //VULKANCONTEXTCREATOR_H
