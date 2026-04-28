#pragma  once
#include "headers/memory.hpp"



class CPU
{
  private:

    uint32_t m_programCounter;
    RegisterFile m_registerFile;

  public:

    CPU(int width = 32)
    : m_programCounter {},
      m_registerFile()
      
    {

    }

    void PC_write(uint32_t data)
    {
      // Write to the PC for branch and jump instructions
      m_programCounter = data;
    }

    void PC_increment(void)
    {
      m_programCounter += 4;
    }

    uint32_t PC_read(void)
    {
      return m_programCounter;
    }

    void Reg_write(uint32_t data, int address)
    {
      m_registerFile.Write(data, address);
    }

    uint32_t Reg_read(int address)
    {
     return m_registerFile.Read(address);
    }

};

