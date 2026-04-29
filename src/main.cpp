#include "headers/cpu.hpp"
#include "headers/decode.hpp"
#include "headers/execute.hpp"
#include "headers/memory.hpp"
#include <cstdint>
#include <iostream>
#include <ostream>

void Step(CPU &CPU, const Memory &Instruction_Memory, Memory *Data_Memory);
void fetch(CPU &CPU, const Memory &Instruction_Memory, Instruction &fields);
void test_inst(Memory &Instruction_Memory);
constexpr int SIZE = 1024;

int main(int argc, char *argv[]) {

  if (argc > 3) {
    std::cout << argv[1] << std::endl;
    std::cout << "Invalid args" << std::endl;
    return 1;
  }

  // Create CPU object with register file + pc
  CPU cpu;

  // Create memory and load instructions
  Memory Instruction_Memory;

  //  TEST
  ///////////////////////////////////////////////
  uint32_t inst = 0x003100b3;
  Instruction_Memory.Write(inst, 0);
  cpu.Reg_write(10, 2);
  cpu.Reg_write(10, 3);
  ///////////////////////////////////////////////
  // Create memory for Data
  Memory *Data_Memory = new Memory(SIZE);

  Step(cpu, Instruction_Memory, Data_Memory);

  std::cout << "Instruction :";
  std::cout << std::hex << Instruction_Memory.Read_Word(0) << std::endl;
  std::cout << "register x1 :";
  std::cout << std::dec << cpu.Reg_read(1) << std::endl;

  delete Data_Memory;
}

void Step(CPU &CPU, const Memory &Instruction_Memory, Memory *Data_Memory) {

  Instruction Instruction_fields = {};

  int num_instr = Instruction_Memory.number_of_words();

  // Loop until all instruction completed
  for (int cycles = 0; cycles < num_instr; cycles++) {
    fetch(CPU, Instruction_Memory, Instruction_fields);
    decode(Instruction_fields);
    execute(CPU, Data_Memory, Instruction_fields);
  }
}

void fetch(CPU &CPU, const Memory &Instruction_Memory, Instruction &fields) {

  // Fetch the instruction and store it in the instruction register
  // Address of instruction to fetch = value in program counter
  fields.instruction = Instruction_Memory.Read_Word(CPU.PC_read());

  // PC += 4
  CPU.PC_increment();
}

// void test_inst(Memory &Instruction_Memory) {

// }
