//
// Created by reece on 29/03/23.
//

#pragma once

// ---------- Standard Library includes

// Utility
#include <cstdint> // (u)int*_t
#include <cstddef> // size_t

// Streams
#include <iostream> // std::cout, std::cin
#include <fstream>  // std::ifstream, std::ofstream
#include <sstream>  // std::ostringstream

// Containers
#include <vector>  // std::vector<>
#include <set>     // std::set<>
#include <array>   // std::array<>
#include <variant> // std::variant


// Type Traits
#include <type_traits> // many things

// ---------- Dependencies
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>


// ---------- Project Utility
#include <VulkanRenderer/api.hpp>
#include <VulkanRenderer/Utility/Wrapper.hpp>
#include <VulkanRenderer/Utility/result.hpp>

namespace vulren::util
{
using namespace cpp;
}

// ---------- Macros
#define CHECK_RESULT(result) if ((result).has_error()) {throw std::runtime_error(result.error());} static_assert(true)