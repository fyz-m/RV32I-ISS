#pragma once
#include <array>
#include <cstdint>
#include <vector>

constexpr int REGISTER_FILE_SIZE = 32;

class RegisterFile {
private:
  std::array<uint32_t, REGISTER_FILE_SIZE> m_registers{};
  int m_width;
public:

  RegisterFile(int width = 32);

  void Write(int address, int32_t data);

  int32_t Read(int address) const;
};

class Memory {

private:
  // RISC-V uses byte-addressable memory, so memory must be an array of bytes
  std::vector<uint8_t> m_memory{};
  int m_WORD_SIZE;
  int m_INSTRUCTION_SIZE;

public:

  Memory(int size = 512, int word_size = 32);

  void Write(uint8_t data, int address);

  void Write(uint32_t data, int address);

  void Write(uint16_t data, int address);

  uint8_t Read_Byte(int address) const;

  uint32_t Read_Word(int address) const;

  uint16_t Read_halfWord(int address) const;

  bool Load(const char *filepath);

  int number_of_words() const;
};


