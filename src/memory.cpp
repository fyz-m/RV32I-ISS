#include "headers/memory.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>

// TODO: add error checking for out of bounds index
void RegisterFile::Write(uint32_t data, int address) {
  // Register x0 is hardwired to 0 so writes to the first register are ignored
  if (address == 0)
    return;

  m_registers[address] = data;
}

uint32_t RegisterFile::Read(int address) const { return m_registers[address]; }

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

void Memory::Write(uint8_t data, int address) {
  // Write a byte

  if (static_cast<long>(address) >= std::ssize(m_memory)) {
    m_memory.resize(address + 1);
  }
  m_memory[address] = data;
}

void Memory::Write(uint32_t data, int address) {
  // Write a word (32-bit)

  for (int i = 0; i < 4; i++) {
    uint8_t data_byte = data >> (i * 8);
    Write(data_byte, address + i);
  }
}

uint8_t Memory::Read_Byte(int address) const { return m_memory[address]; }

uint32_t Memory::Read_Word(int address) const {
  uint32_t word{};

  for (int i = 0; i < 4; i++) {
    auto byte = static_cast<uint32_t>(Read_Byte(address + i));

    word |= byte << (8 * i);
  }
  return word;
}

bool Memory::Load(const char *filepath) {
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

int Memory::number_of_words() const {
  // number of bytes / word_size
  return (std::ssize(m_memory) * 8) / m_WORD_SIZE;
}
