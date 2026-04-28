#pragma once
#include "cpu.hpp"
#include "memory.hpp"
#include <cstdint>
#include <memory>

extern std::unique_ptr <Memory> instruction_memory;

extern std::unique_ptr <Memory> data_memory;

extern std::unique_ptr <CPU> cpu;

extern std::unique_ptr <std::uint32_t> instruction_register;