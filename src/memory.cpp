#include <cstdint>
#include <array>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
#include <stdio.h>


constexpr int REGISTER_FILE_SIZE = 32; 

class RegisterFile
{
  private:

     std::array <uint32_t, REGISTER_FILE_SIZE> m_registers{}; // RISC-V architecture contains 32 registers
     
  public:

    // TODO: add error checking for out of bounds index
    void Write(uint32_t data, int address)
    {
      // Register x0 is hardwired to 0 so writes to the first register are ignored
      if (address == 0)
        return;

      m_registers[address] = data;
    }

    uint32_t Read(int address)
    {      
      return m_registers[address];
    }
    
    
};



// Memory Class (32-bit so max 4GB)
// TODO:
// out of bounds checking
// read/write half words (16 bits)
class Memory
{

  private:
    // byte-addressable memeory so memory must be an array of bytes
    std::vector <uint8_t> m_memory {};
    int m_WORD_SIZE;
    int  m_INSTRUCTION_SIZE;

  public:
    
    Memory(int size = 512, int word_size = 32)
      : m_WORD_SIZE {word_size},
        m_INSTRUCTION_SIZE {word_size / 8} // number of bytes 
    {
      m_memory.reserve(size);
      
    }

    void Write(uint8_t data, int address)
    {
      // Write a byte
      m_memory[address] = data;
    }
    
    void Write(uint32_t data, int address)
    {
      // Write a word (32-bit)
  
      for (int i = 0; i < 4; i++)
      {
        uint8_t data_byte = data >> (i * 8); 
        Write(data_byte, address + i); 
      }

    }

    uint8_t Read_Byte(int address)
    {
      return m_memory[address];
    }

    uint32_t Read_Word(int address)
    {
      uint32_t word {};

      for (int i = 0; i < 4; i++)
      {
        auto byte = static_cast<uint32_t>(Read_Byte(address + i));

        word |= byte << (8 * i);
      }
      return word;
    }

     bool Load(const char *file)
    {
      // Load contents of a file into the memory
      std::ifstream input_file{file, std::ios::binary};

      if (!input_file)
      {
          std::cerr << "Could not open file";
          return false;
      }
      
      uint32_t inst;
      while (input_file.read( reinterpret_cast<char*>(&inst), sizeof(inst)))
      {
        m_memory.push_back(inst);
      }

      input_file.close();
      return true;
    }
};
