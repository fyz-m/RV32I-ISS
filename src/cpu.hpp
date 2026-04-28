#pragma  once
#include "headers/memory.hpp"

class CPU
{
  private:

    uint32_t m_programCounter;
    RegisterFile m_registerFile;

  public:

    CPU(int width = 32);
    

    void PC_write(uint32_t data);
    

    void PC_increment(void);
    

    uint32_t PC_read(void);
   

    void Reg_write(uint32_t data, int address);
  

    uint32_t Reg_read(int address);
   

};
