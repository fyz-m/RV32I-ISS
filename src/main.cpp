#include "headers/cpu.hpp"
#include "headers/decode.hpp"
#include "headers/execute.hpp"
#include "headers/memory.hpp"
#include <cstdint>
#include <iostream>
#include <ostream>

void Step(CPU &CPU, const Memory *Instruction_Memory, Memory *Data_Memory);
void fetch(CPU &CPU, const Memory *instruction_mem, Instruction *inst);
void test_inst(Memory &Instruction_Memory);
constexpr int SIZE = 1024;

int main(int argc, char *argv[]) {

  if (argc > 3) {
    std::cout << argv[1] << std::endl;
    std::cout << "Invalid args" << std::endl;
    return 1;
  }

  // Create CPU object with register file + pc
  CPU CPU;

  // Create memory and load instructions
  Memory *Instruction_Memory = new Memory(SIZE);
  if (Instruction_Memory == nullptr) {
    std::cerr << "Unable to create Instruction Memory" << std::endl;
  }

  // TEMP TESTS
  uint32_t inst = 0x003100b3;
  Instruction_Memory->Write(inst, 0);

  // Create memory for Data
  Memory *Data_Memory = new Memory(SIZE);
  if (Data_Memory == nullptr) {
    std::cerr << "Unable to create Data Memory" << std::endl;
  }

  Step(CPU, Instruction_Memory, Data_Memory);

  delete Data_Memory;
  delete Instruction_Memory;
}

void Step(CPU &CPU, const Memory *Instruction_Memory, Memory *Data_Memory) {

  Instruction *instr = new (Instruction);
  if (instr == nullptr) {
    std::cerr << "Unable to create Instruction struct" << std::endl;
  }

  int num_instr = Instruction_Memory->number_of_words();

  // Loop until all instruction completed
  for (int cycles = 0; cycles < num_instr; cycles++) {
    fetch(CPU, Instruction_Memory, instr);
    decode(instr);
    execute(CPU, Data_Memory, instr);
  }

  delete instr;
}

void fetch(CPU &CPU, const Memory *instruction_mem, Instruction *inst) {

  // Fetch the instruction and store it in the instruction register
  // Address of instruction to fetch = value in program counter
  inst->instruction = instruction_mem->Read_Word(CPU.PC_read());

  // PC += 4
  CPU.PC_increment();
}

// void test_inst(Memory &Instruction_Memory) {

// }
