//
// Created by erik on 01.05.24.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "Window.h"
#include "Vulkan/Structs/VulkanContext.h"

class Application {

public:
    Application();

    void Run() const;

private:

    Window Window;
    VulkanContext VulkanContext;
};



#endif //APPLICATION_H
