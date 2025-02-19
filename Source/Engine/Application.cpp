//
// Created by erik on 01.05.24.
//

#include "StdAfx.h"
#include "Application.h"

#include "Vulkan/VulkanContextCreator.h"

Application::Application()
    : AppWindow(::Window(WindowProps("Card Game", 800, 600))),
      VkContext(VulkanContextCreator::Create(AppWindow)) {}

void Application::Run() const {

    while (AppWindow.IsOpen()) {
        AppWindow.PollEvents();
        AppWindow.Present();
    }

}
