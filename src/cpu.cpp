
#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include <cstdint>

CPU::CPU(int) : m_programCounter{}, m_registerFile() {}

void CPU::PC_write(uint32_t data) 
{
  // Write to the PC for branch and jump instructions
  m_programCounter = data;
}

void CPU::PC_increment(void) 
{
   m_programCounter += 4; 
}

uint32_t CPU::PC_read(void) const
{ 
  return m_programCounter; 
}

void CPU::Reg_write(uint32_t data, int address) {
  m_registerFile.Write(data, address);
}

uint32_t CPU::Reg_read(int address) const 
{ 
  return m_registerFile.Read(address); 
}
