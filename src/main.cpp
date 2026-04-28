#pragma once
#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include <memory>

void Step(char* filename);
void fetch();
void decode();
void execute();

// Instantiate memory containing instructions
std::unique_ptr <Memory> instruction_memory = std::make_unique <Memory>(); 

// Create memory for data
constexpr int DATA_SIZE = 1024;
std::unique_ptr <Memory> data_memory = std::make_unique <Memory>(DATA_SIZE);

// Create CPU
std::unique_ptr <CPU> cpu = std::make_unique <CPU>();


int main(int argc, char *argv[])
{

  Step(argv[2]);
}

void Step(char* filename)
{
  fetch();
  decode();
  execute();
}

void fetch()
{
  // Fetch instruction from the instruction memory 
  // Address of instruction to fetch is the current value of the program counter
  auto instruction = instruction_memory->Read_Word( cpu->PC_read());

  
}