#include "headers/cpu.hpp"
#include "headers/decode.hpp"
#include "headers/execute.hpp"
#include "headers/memory.hpp"
#include <cstdint>
#include <iostream>

void load_file(char *filename);
void Step(CPU& CPU, Memory& instruction_mem, Memory *data_mem); 
void fetch(CPU& CPU, const Memory& instruction_mem, Instruction *inst);

constexpr int SIZE = 1024;



int main(int argc, char *argv[]) 
{

  if (argc != 2) 
  {
    std::cout << "Invalid args" << std::endl;
    return 1;
  }

  // Create CPU object with register file + pc
  CPU CPU; 

  // Create memory and load instructions
  Memory Instruction_Memory;
  Instruction_Memory.Load(argv[2]);

  // Create memory for Data
  Memory *Data_Memory = new Memory(SIZE);

  Step(CPU, Instruction_Memory , Data_Memory);

}

void Step(CPU& CPU, const Memory& Instruction_Memory, Memory *Data_Memory) 
{

  Instruction *instr {};

  int num_instr = Instruction_Memory.number_of_words();  

  // Loop until all instruction completed
  for (int cycles = 0; cycles < num_instr; cycles++) 
  {
    fetch(CPU, Instruction_Memory, instr);
    decode(instr);
    execute(CPU, Data_Memory, instr);
  }
}

void fetch(CPU& CPU, const Memory& instruction_mem, Instruction *inst)
{
 // Fetch the instruction and store it in the instruction register
 // Address of instruction to fetch = value in program counter
  inst->instruction = instruction_mem.Read_Word( CPU.PC_read()); 

  // PC += 4
  CPU.PC_increment();
}