//
// Created by reece on 04/04/23.
//

#pragma once

#include <VulkanRenderer/common.hpp>

namespace vulren
{

/// The window class contains basic functionality for creating and managing windows.
class Window: public util::PtrWrapper<GLFWwindow>
{
public:
    /// InitInfo holds information required to initialise the class.
    struct InitInfo
    {
        int width, height;
        const char* title;
    };
public:
    /// The default constructor allows for delayed initialisation of the class.
    VULREN_EXPORT Window() noexcept;
    /// The destructor will close the window if this is not done already.
    VULREN_EXPORT ~Window() noexcept;

    /// Will immediately initialise the window, passes the values to the correct init function.
    VULREN_EXPORT Window(int width, int height, const char* title);
    /// Will immediately initialise the window, passes the structure values to the correct init function.
    VULREN_EXPORT Window(const InitInfo& init_info);

    /// Copying a window is not allowed.
    VULREN_EXPORT Window(const Window&) = delete;
    /// Copying a window is not allowed.
    VULREN_EXPORT Window& operator=(const Window&) = delete;

    /// Take ownership of another window.
    VULREN_EXPORT Window(Window&& other) noexcept;
    /// Take ownership of another window, and close any currently owned window.
    VULREN_EXPORT Window& operator=(Window&& other) noexcept;

    /// Initialise the window using an InitInfo structure, passes the structure values to the correct init function.
    VULREN_EXPORT vulren::util::result<void, std::string> init(const InitInfo& info) noexcept;
    /// Initialise the class and create the window.
    VULREN_EXPORT vulren::util::result<void, std::string> init(int width, int height, const char* title) noexcept;

    /// Retrieves the internal pointer to the window, needed for PtrWrapper.
    VULREN_EXPORT GLFWwindow* get() override;
    /// Retrieves the InitInfo structure used to initialise the class.
    VULREN_EXPORT util::result<const vulren::Window::InitInfo&, std::string> init_info() const noexcept;

    /// Retrieves the width of the window by querying glfw.
    VULREN_EXPORT util::result<int, std::string> width() const noexcept;
    /// Retrieves the height of the window by querying glfw.
    VULREN_EXPORT util::result<int, std::string> height() const noexcept;
    /// Retrieves the size of the window by querying glfw.
    VULREN_EXPORT util::result<glm::ivec2, std::string> size() const noexcept;

    /// Sets the width of the window.
    VULREN_EXPORT util::result<void, std::string> set_width(int width) noexcept;
    /// Sets the height of the window.
    VULREN_EXPORT util::result<void, std::string> set_height(int height) noexcept;
    /// Sets the size of the window.
    VULREN_EXPORT util::result<void, std::string> set_size(glm::ivec2 size) noexcept;

    /// Closes the window.
    VULREN_EXPORT void close() noexcept;
    /// Checks if the window is in a valid state.
    VULREN_EXPORT bool is_open() noexcept;

    /// Retrieves whether the window has been resized since creation. Can be cleared with clear_resized().
    VULREN_EXPORT util::result<bool, std::string> has_resized() const noexcept;
    /// Clears the has_resized flag.
    VULREN_EXPORT util::result<void, std::string> clear_resized() noexcept;

public:
    /// Polls all GLFW events.
    VULREN_EXPORT static void PollEvents() noexcept;
    /// Notifies a window when it has been resized.
    static void WindowSizeCallback(GLFWwindow* window, int width, int height) noexcept;

private:
    /// Sets the has_resized flag.
    util::result<void, std::string> notify_resize();

private:
    /// The InitInfo structure that was used to initialise the class.
    InitInfo m_init_info;
    /// The window held by the class.
    GLFWwindow* m_window;
    /// The flag that holds whether the window has been resized.
    bool m_has_resized;

private:
    /// The number of references to glfw, used to call glfwInit and glfwTerminate correctly.
    static unsigned int s_glfw_references;
};

}
