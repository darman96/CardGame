//
// Created by erik on 01.05.24.
//

#include "StdAfx.h"
#include "Application.h"

#include "Vulkan/VulkanContextCreator.h"

Application::Application()
    : Window(::Window(WindowProps("Card Game", 800, 600))),
      VulkanContext(VulkanContextCreator::Create(Window)) {}

void Application::Run() const {

    while (Window.IsOpen()) {
        Window.PollEvents();
        Window.Present();
    }

}
