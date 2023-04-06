//
// Created by reece on 25/03/23.
//

#include <VulkanRenderer/VulkanRenderer.hpp>

int main()
{
    vulren::Window window;

    vulren::Window::InitInfo init_info{};
    init_info.width = 640;
    init_info.height = 480;
    init_info.title = "Hello, World!";
    CHECK_RESULT(window.init(init_info));

    while (window.is_open())
    {
        vulren::Window::PollEvents();
    }
}

