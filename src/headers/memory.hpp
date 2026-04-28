#pragma once
#include <cstdint>
#include <array>
#include <vector>
#include <cstdint>

constexpr int REGISTER_FILE_SIZE = 32;

class RegisterFile
{
  private:
    std::array <uint32_t, REGISTER_FILE_SIZE> m_registers{};
  public:
   
    void Write(uint32_t data, int address);

    uint32_t Read(int address);
};

class Memory
{

  private:
    // byte-addressable memeory so memory must be an array of bytes
    std::vector <uint8_t> m_memory {};
    int m_WORD_SIZE;
    int  m_INSTRUCTION_SIZE;

  public:
    
    Memory(int size = 512, int word_size = 32);
      
    void Write(uint8_t data, int address);
       
    void Write(uint32_t data, int address);
       
    uint8_t Read_Byte(int address);
   
    uint32_t Read_Word(int address);
  
    bool Load(const char *file);
    
};