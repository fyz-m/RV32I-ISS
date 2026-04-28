#pragma once
#include "headers/Globals.hpp"
#include "headers/memory.hpp"
#include <cstdint>
#include <memory>

constexpr int DATA_SIZE = 1024;

auto instruction_memory = std::make_unique <Memory> ();

auto data_memory = std::make_unique <Memory> (DATA_SIZE);

auto cpu = std::make_unique <CPU> ();

auto instruction_register = std::make_unique <uint32_t> ();