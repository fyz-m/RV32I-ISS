#pragma once
#include "headers/Globals.hpp"
#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include "headers/decode.hpp"
#include "headers/execute.hpp"
#include <iostream>
#include <memory>

void Step(char* filename);
void fetch();
void check_ptr();

int main(int argc, char *argv[])
{
  check_ptr();
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
   *instruction_register = instruction_memory->Read_Word( cpu->PC_read());

  // Increment program counter to next address
  cpu->PC_increment();
}

void check_ptr()
{
  if (instruction_memory == nullptr ||
      data_memory == nullptr ||
      cpu == nullptr ||
      instruction_register == nullptr)
      {
        std::cerr << "Could not initialize global pointer " << std::endl;
      }
}