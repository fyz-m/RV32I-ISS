#include "headers/memory.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>

// TODO: add error checking for out of bounds index

  RegisterFile::RegisterFile(int width)
      : WIDTH(width)
      {
        registers[0] = 0;
      }

  void RegisterFile::Write(int address, uint32_t data) 
  {
    validate_address(address);
    // Register x0 is hardwired to 0 so writes to the first register are ignored
    if (address == 0)
      return;

    registers[address] = data;
  }

  uint32_t RegisterFile::Read(int address) const 
  { 
    validate_address(address);
    return registers[address]; 
  }

  void RegisterFile::validate_address(int& address) const
  {
    if ( !(0 <= address && address < REGISTER_FILE_SIZE) )
      throw std::out_of_range("Invalid register");
  }



// TODO:
// out of bounds checking
  Memory::Memory(int size)     
  {
    m_memory.reserve(size);
    m_memory.resize(1);
  }

  void Memory::Write(uint8_t data, std::size_t address) 
  {
    // Write a byte at address

    // If address is greater than current length, resize vector
    if (address >= std::size(m_memory)) {
      m_memory.resize(address + 1);
    }
    m_memory[address] = data;
  }

  void Memory::Write(uint32_t data, std::size_t address) 
  {
    // Write a word (4 bytes)
    for (int i = 0; i < 4; i++) 
    {
      uint8_t data_byte = data >> (i * 8);
      Write(data_byte, address + i);
    }
  }

  void Memory::Write(uint16_t data, std::size_t address)
  {
    // Write a half-word (2 bytes)
    for (int i = 0; i < 2; i++) 
    {
      // Extract byte to write
      uint8_t data_byte = data >> (i * 8);
      Write(data_byte, address + i);
    }
  }

  uint8_t Memory::Read_Byte(std::size_t address) const 
  { 
    return m_memory[address]; 
  }

  uint32_t Memory::Read_Word(std::size_t address) const 
  {
    uint32_t word{};

    for (int i = 0; i < 4; i++) {
      auto byte = static_cast<uint32_t>(Read_Byte(address + i));

      word |= byte << (8 * i);
    }
    return word;
  }

  uint16_t Memory::Read_halfWord(std::size_t address) const
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

  