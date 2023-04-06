//
// Created by reece on 04/04/23.
//

#include "Window.hpp"


unsigned int vulren::Window::s_glfw_references = 0;

vulren::Window::Window() noexcept
        : m_init_info{}, m_window{nullptr}, m_has_resized{false}
{
}

vulren::Window::~Window() noexcept
{
    // Close the window when the class is destructed.
    close();
}

vulren::Window::Window(int width, int height, const char* title)
        : m_init_info{}, m_window{nullptr}, m_has_resized{false}
{
    // Initialise the class.
    CHECK_RESULT(init(width, height, title));
}

vulren::Window::Window(const vulren::Window::InitInfo& init_info)
        : m_init_info{}, m_window{nullptr}, m_has_resized{false}
{
    // Initialise the class.
    CHECK_RESULT(init(init_info.width, init_info.height, init_info.title));
}

vulren::Window::Window(vulren::Window&& other) noexcept
        : m_init_info{}, m_window{nullptr}, m_has_resized{false}
{
    m_window = other.m_window;
    other.m_window = nullptr;

    m_init_info = other.m_init_info;
}

vulren::Window& vulren::Window::operator =(vulren::Window&& other) noexcept
{
    // Avoid moving into self.
    if (&other == this) return *this;

    // Close this window.
    close();
    m_window = other.m_window;
    other.m_window = nullptr;

    m_init_info = other.m_init_info;

    return *this;
}


vulren::util::result<void, std::string> vulren::Window::init(const vulren::Window::InitInfo& info) noexcept
{
    // Pass the structure info to the actual init function.
    return init(info.width, info.height, info.title);
}

vulren::util::result<void, std::string> vulren::Window::init(int width, int height, const char* title) noexcept
{
    // If the class is already initialised, close the old window.
    close();

    // If this is the first window, then glfw will not be initialised.
    // This makes sure glfw is always initialised as long as there is a window open.
    if (s_glfw_references++ == 0)
    {
        if (!glfwInit()) return util::fail("Window::init(): Failed to create window, glfw failed to initialise");
    }

    // Sizes cannot be zero or negative.
    if (width <= 0) return util::fail("Window::init(): Failed to create window, invalid width given");
    if (height <= 0) return util::fail("Window::init(): Failed to create window, invalid height given");

    // We are using vulkan, so there is no need for opengl.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Window resizing is supported.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // Attempt to create the window, if it is null, return an error.
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) return util::fail("Window::init(): Failed to create window, glfwCreateWindow failed");

    // Store the window.
    m_window = window;

    // Tiling window managers such as: dwm, i3, bspwm and awesome will ignore the requested window size.
    // So we need to check the actual size of the window.
    int actual_width, actual_height;
    glfwGetWindowSize(m_window, &actual_width, &actual_height);

    if (width != actual_width || height != actual_height)
    {
        std::cout << "Window::init(): Warning, Window dimensions were not respected. Actual size "
                     "{" << actual_width << ", " << actual_height << "}\n";
    }

    // Store the info used to initialise.
    m_init_info = {width, height, title};
    // Set the user pointer to this class instance.
    glfwSetWindowUserPointer(m_window, this);

    // Enable the resize callback.
    glfwSetWindowSizeCallback(m_window, WindowSizeCallback);

    return {};
}


GLFWwindow* vulren::Window::get()
{
    return m_window;
}

vulren::util::result<const vulren::Window::InitInfo&, std::string> vulren::Window::init_info() const noexcept
{
    if (m_window == nullptr)
        return util::fail("Window::init_info(): Cannot get create information, the window is not initialised");
    return m_init_info;
}

vulren::util::result<int, std::string> vulren::Window::width() const noexcept
{
    if (m_window == nullptr) return util::fail("Window::width(): Cannot get width, the window is not initialised");
    return size()->x;
}

vulren::util::result<int, std::string> vulren::Window::height() const noexcept
{
    if (m_window == nullptr) return util::fail("Window::height(): Cannot get height, the window is not initialised");
    return size()->y;
}

vulren::util::result<glm::ivec2, std::string> vulren::Window::size() const noexcept
{
    if (m_window == nullptr) return util::fail("Window::size(): Cannot get size, the window is not initialised");

    glm::ivec2 size;
    glfwGetWindowSize(m_window, &size.x, &size.y);

    return size;
}

vulren::util::result<void, std::string> vulren::Window::set_width(int width) noexcept
{
    if (m_window == nullptr) return util::fail("Window::set_width(): Cannot set width, the window is not initialised");
    if (width <= 0) return util::fail("Window::set_width(): Cannot set width, invalid width given");

    return set_size({width, size()->y});
}

vulren::util::result<void, std::string> vulren::Window::set_height(int height) noexcept
{
    if (m_window == nullptr)
        return util::fail("Window::set_height(): Cannot set height, the window is not initialised");
    if (height <= 0) return util::fail("Window::set_height(): Cannot set height, invalid height given");

    return set_size({size()->x, height});
}

vulren::util::result<void, std::string> vulren::Window::set_size(glm::ivec2 size) noexcept
{
    if (m_window == nullptr)
        return util::fail("Window::set_size(): Cannot set size, the window is not initialised");
    if (size.x <= 0 || size.y <= 0) return util::fail("Window::set_height(): Cannot set size, invalid size given");

    glfwSetWindowSize(m_window, size.x, size.y);

    return notify_resize();
}


void vulren::Window::close() noexcept
{
    // m_window is nullptr when either the class is not initialised, or the window was closed,
    // either way it is successful.
    if (m_window == nullptr)
        return;

    glfwDestroyWindow(m_window);
    m_window = nullptr;

    // If this was the only remaining window, then glfw can be terminated.
    if (--s_glfw_references == 0) glfwTerminate();
}

bool vulren::Window::is_open() noexcept
{
    return m_window != nullptr && !glfwWindowShouldClose(m_window);
}


vulren::util::result<bool, std::string> vulren::Window::has_resized() const noexcept
{
    if (m_window == nullptr)
        return util::fail("Window::has_resized(): Failed to check for resize, the window is not initialised");

    return m_has_resized;
}

vulren::util::result<void, std::string> vulren::Window::clear_resized() noexcept
{
    if (m_window == nullptr)
        return util::fail("Window::clear_resized(): Failed to clear resize, the window is not initialised");

    m_has_resized = false;

    return {};
}

void vulren::Window::PollEvents() noexcept
{
    glfwPollEvents();
}

void vulren::Window::WindowSizeCallback(GLFWwindow* window, int, int) noexcept
{
    void* user_pointer = glfwGetWindowUserPointer(window);
    if (user_pointer == nullptr) return;

    Window* p_wnd = reinterpret_cast<Window*>(user_pointer);
    CHECK_RESULT(p_wnd->notify_resize());
}


vulren::util::result<void, std::string> vulren::Window::notify_resize()
{
    if (m_window == nullptr)
        return util::fail("Window::notify_resize(): Failed to notify resize, the window is not initialised");

    m_has_resized = true;

    return {};
}

