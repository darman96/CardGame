//
// Created by erik on 03.05.24.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <utility>

namespace vk {
    class Instance;
    class SurfaceKHR;
}

struct WindowProps {
    std::string title;
    uint width;
    uint height;

    WindowProps(std::string title, const uint width, const uint height)
        : title(std::move(title)), width(width), height(height) {}
};

class Window {
    friend class VulkanSurfaceCreator;

public:
    explicit Window(const WindowProps& windowProps);
    ~Window();

    void PollEvents() const;
    void Present() const;
    [[nodiscard]] bool IsOpen() const;
    [[nodiscard]] std::tuple<uint32, uint32> GetFramebufferSize() const;

private:

    struct GLFWwindow* window;
};



#endif //WINDOW_H
