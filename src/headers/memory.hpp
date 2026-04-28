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

    uint32_t Read(int address) const;
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
       
    uint8_t Read_Byte(int address) const;
   
    uint32_t Read_Word(int address) const;
  
    bool Load(const char *filepath);

    int number_of_words() const;
    
};

typedef struct Instruction {
    uint32_t instruction {};
    uint8_t opcode {};
    uint8_t funct3 {};
    uint8_t funct7 {};
    uint8_t rs1 {};
    uint8_t rs2 {};
    uint8_t rd {};
    uint32_t imm {};

  } Instruction;