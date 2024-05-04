//
// Created by erik on 01.05.24.
//

#include "StdAfx.h"
#include "Application.h"
#include "Window.h"
#include "VulkanContext.h"

Application::Application() {
    const auto windowProps = WindowProps("Card Game", 800, 600);
    window = std::make_shared<Window>(Window(windowProps));
    vulkanContext = std::make_unique<VulkanContext>(VulkanContext());
}

Application::~Application() = default;

void Application::Run() const {
    vulkanContext->CreateSurface(window.get());

    while (window->IsOpen()) {
        window->PollEvents();
        window->Present();
    }

}
