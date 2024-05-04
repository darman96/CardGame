//
// Created by erik on 03.05.24.
//
#include "StdAfx.h"
#include "Window.h"

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "vulkan/vulkan.hpp"

Window::Window(const WindowProps &windowProps) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(
        static_cast<int>(windowProps.width),
        static_cast<int>(windowProps.height),
        windowProps.title.c_str(),
        nullptr, nullptr);

    if (!window) {
        throw std::runtime_error("Failed to create window");
    }
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::PollEvents() const {
    glfwPollEvents();
}

void Window::Present() const {
    glfwSwapBuffers(window);
}

bool Window::IsOpen() const {
    return glfwWindowShouldClose(window) == false;
}

vk::SurfaceKHR* Window::createSurface(const vk::Instance *vulkanInstance) const {
    VkSurfaceKHR surface;
    if (const auto result = glfwCreateWindowSurface(*vulkanInstance, window, nullptr, &surface); result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface, error code: " + std::to_string(result));
    }

    return new vk::SurfaceKHR(surface);
}
