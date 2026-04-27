#include <cstdint>
#include <array>
#include <vector>

// Register File Class

// ignore writes to regfile[0]
// In RISC-V register x0 is hardwired to 0

// Method to write and read the register file
class RegisterFile
{
  private:

     std::array <uint32_t, 32> m_registers{}; // RISC-V architecture contains 32 registers
     
  public:

    RegisterFile()
    {
      
    }
    
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
      if (address == 0)
        return 0;

      return m_registers[address];
    }
    
    
};



// Memory Class (32-bit so max 4GB)
class Memory
{

  private:
    // byte-addressable memeory 
    std::vector <uint8_t> m_memory;
    int WORD_SIZE = 32;
  public:
    
    Memory()
    {
      m_memory.reserve(512);
    }
    Memory(int size)
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
};

