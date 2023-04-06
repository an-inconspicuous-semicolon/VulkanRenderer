//
// Created by reece on 06/04/23.
//

#include <VulkanRenderer/VulkanRenderer.hpp>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

#define TEST(result, code, name) \
{ bool output = (code);            \
if (!output)                     \
{std::cout << "[FAILED]: " << name << '\n';} \
else {std::cout << "[PASSED]: " << name << '\n';} \
result = result && output;        \
}


bool is_window_valid(vulren::Window& window)
{
    return window.get() != nullptr;
}

bool test_default()
{
    try
    {
        vulren::Window window;
        return true;
    } catch(...)
    {
        return false;
    }
}


bool test_direct_param()
{
    try
    {
        vulren::Window window(100, 100, "Test");
        return is_window_valid(window);
    } catch(...)
    {
        return false;
    }
}

bool test_direct_struct()
{
    try
    {
        vulren::Window::InitInfo init_info{100, 100, "Test"};
        vulren::Window window(init_info);
        return is_window_valid(window);
    } catch(...)
    {
        return false;
    }
}


bool test_delayed_param()
{
    try
    {
        vulren::Window window;
        CHECK_RESULT(window.init(100, 100, "Test"));
        return is_window_valid(window);
    } catch(...)
    {
        return false;
    }
}

bool test_delayed_struct()
{
    try
    {
        vulren::Window::InitInfo init_info{100, 100, "Test"};
        vulren::Window window;
        CHECK_RESULT(window.init(init_info));
        return is_window_valid(window);
    } catch(...)
    {
        return false;
    }
}

bool test_getting_window(vulren::Window& window)
{
    return window.get() != nullptr;
}

bool test_getting_width(vulren::Window& window, int expected)
{
    auto result = window.width();
    if (result.has_error()) return false;
    return result.value() == expected;
}

bool test_getting_height(vulren::Window& window, int expected)
{
    auto result = window.height();
    if (result.has_error()) return false;
    return result.value() == expected;
}

bool test_getting_size(vulren::Window& window, glm::ivec2 expected)
{
    auto result = window.size();
    if (result.has_error()) return false;
    return result.value() == expected;
}

bool test_setting_width(vulren::Window& window, int value)
{
    auto result = window.set_width(value);
    if (result.has_error()) return false;
    std::this_thread::sleep_for(100ms);
    return window.width().value() == value;
}

bool test_setting_height(vulren::Window& window, int value)
{
    auto result = window.set_height(value);
    if (result.has_error()) return false;
    std::this_thread::sleep_for(100ms);
    return window.height().value() == value;
}

bool test_setting_size(vulren::Window& window, glm::ivec2 value)
{
    auto result = window.set_size(value);
    if (result.has_error()) return false;
    std::this_thread::sleep_for(100ms);
    return test_getting_size(window, value);
}

bool test_resize()
{
    vulren::Window window(100, 100, "Test");
    std::this_thread::sleep_for(100ms);
    auto result = window.has_resized();
    if (result.has_error()) return false;

    bool has_resize = result.value();
    if (has_resize) return false;

    auto result2 = window.set_size({150, 150});
    std::this_thread::sleep_for(100ms);
    if (result2.has_error()) return false;

    auto result3 = window.has_resized();
    if (result3.has_error()) return false;
    return result3.value();
}

bool test_clear_resize()
{
    vulren::Window window(100, 100, "Test");

    auto result = window.set_size({150, 150});
    std::this_thread::sleep_for(100ms);
    if (result.has_error()) return false;

    auto result2 = window.has_resized();
    if (result2.has_error()) return false;

    bool has_resize_1 = result2.value();

    auto result3 = window.clear_resized();
    std::this_thread::sleep_for(100ms);
    if (result3.has_error()) return false;

    auto result4 = window.has_resized();
    if (result4.has_error()) return false;

    bool has_resize_2 = result4.value();

    return has_resize_1 && !has_resize_2;
}

int main()
{
    bool result = true;
    TEST(result, test_default(), "Default Construction")
    TEST(result, test_direct_param(), "Construction with parameters")
    TEST(result, test_direct_struct(), "Construction with structure")
    TEST(result, test_delayed_param(), "Delayed initialisation with parameters")
    TEST(result, test_delayed_struct(), "Delayed initialisation with structure")


    vulren::Window window(100, 100, "Test");
    TEST(result, test_getting_window(window), "Getting window")
    TEST(result, test_getting_width(window, 100), "Getting width")
    TEST(result, test_getting_height(window, 100), "Getting height")
    TEST(result, test_getting_size(window, {100, 100}), "Getting size")
    TEST(result, test_setting_width(window, 200), "Setting width")
    TEST(result, test_setting_height(window, 200), "Setting height")
    TEST(result, test_setting_size(window, {100, 100}), "Setting size")
    TEST(result, test_resize(), "Checking for resize")
    TEST(result, test_clear_resize(), "Clearing resize")

    return !result;
}