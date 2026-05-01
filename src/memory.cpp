#include "headers/memory.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>

// TODO: add error checking for out of bounds index

  RegisterFile::RegisterFile(int width)
      : m_width(width)
      {}

  void RegisterFile::Write(int address, int32_t data) 
  {
    // Register x0 is hardwired to 0 so writes to the first register are ignored
    if (address == 0)
      return;

    m_registers[address] = data;
  }

  int32_t RegisterFile::Read(int address) const 
  { 
    return m_registers[address]; 
  }



// Memory Class (32-bit so max 4GB)
// TODO:
// out of bounds checking
// read/write half words (16 bits)

  Memory::Memory(int size, int word_size)
      : m_WORD_SIZE{word_size},
        m_INSTRUCTION_SIZE{word_size / 8} // number of bytes
  {
    m_memory.reserve(size);
    m_memory.resize(1);
  }

  void Memory::Write(uint8_t data, int address) 
  {
    // Write a byte at address

    // If address is greater than current length, resize vector
    if (static_cast<long>(address) >= std::ssize(m_memory)) {
      m_memory.resize(address + 1);
    }
    m_memory[address] = data;
  }

  void Memory::Write(uint32_t data, int address) 
  {
    // Write a word (32-bit)

    for (int i = 0; i < 4; i++) {
      uint8_t data_byte = data >> (i * 8);
      Write(data_byte, address + i);
    }
  }

  uint8_t Memory::Read_Byte(int address) const 
  { 
    return m_memory[address]; 
  }

  uint32_t Memory::Read_Word(int address) const 
  {
    uint32_t word{};

    for (int i = 0; i < 4; i++) {
      auto byte = static_cast<uint32_t>(Read_Byte(address + i));

      word |= byte << (8 * i);
    }
    return word;
  }

   uint16_t Memory::Read_halfWord(int address) const
   {
    return static_cast<uint16_t>(Read_Word(address));
   }

  bool Memory::Load(const char *filepath) 
  {
    // Load contents of a file into the memory
    std::ifstream input_file{filepath, std::ios::binary};

    if (!input_file) {
      std::cerr << "Could not open file";
      return false;
    }

    uint32_t inst;
    while (input_file.read(reinterpret_cast<char *>(&inst), sizeof(inst))) {
      m_memory.push_back(inst);
    }

    input_file.close();
    return true;
  }

  int Memory::number_of_words() const 
  {
    // number of bits / word_size (bits per word)
    return (std::ssize(m_memory) * 8) / m_WORD_SIZE;
  }
