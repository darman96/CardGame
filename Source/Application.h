//
// Created by erik on 01.05.24.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

class Application {

public:
    Application();
    ~Application();

    void Run() const;

private:

    std::shared_ptr<class Window> window;
    std::unique_ptr<class VulkanContext> vulkanContext;
};



#endif //APPLICATION_H
