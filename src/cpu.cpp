#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include "headers/decode.hpp"
#include <cstdint>

  CPU::CPU(int) 
    : program_counter{}, register_file() 
    {}


  void CPU::Step()
  {
    Fetch();
    Decode();
    Execute();

  }

  void CPU::Fetch()
  {
    instruction_register = Instruction_Memory.Read_Word(program_counter);
  }

  void CPU::Decode()
  {
    decode(instruction_fields);
  }

  void CPU::Execute()
  {

  }

  void CPU::writePC(uint32_t data) 
  {
    // Write to the PC for branch and jump instructions
    program_counter = data;
  }

  void CPU::incrementPC(void) 
  {
    program_counter += 4; 
  }

  uint32_t CPU::readPC(void) const
  { 
    return program_counter; 
  }

  void CPU::writeReg (int address, int32_t data) 
  {
    register_file.Write(address, data);
  }

  int32_t CPU::readReg(int address) const 
  { 
    return register_file.Read(address); 
  }
