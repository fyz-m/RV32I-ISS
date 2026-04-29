#pragma once
#include <array>
#include <cstdint>
#include <vector>

constexpr int REGISTER_FILE_SIZE = 32;

class RegisterFile {
private:
  std::array<uint32_t, REGISTER_FILE_SIZE> m_registers{};

public:
  void Write(int32_t data, int address);

  int32_t Read(int address) const;
};

class Memory {

private:
  // byte-addressable memeory so memory must be an array of bytes
  std::vector<uint8_t> m_memory{};
  int m_WORD_SIZE;
  int m_INSTRUCTION_SIZE;

public:
  Memory(int size = 512, int word_size = 32);

  void Write(uint8_t data, int address);

  void Write(uint32_t data, int address);

  uint8_t Read_Byte(int address) const;

  uint32_t Read_Word(int address) const;

  bool Load(const char *filepath);

  int number_of_words() const;
};

enum class OPERATION {

  UNKNOWN,
  // R-type
  ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND,
  // I-type
  LB, LH, LW, LBU, LHU, ADDI, SLLI, SLTI, SLTIU, XORI, SRLI, SRAI, ORI, ANDI, JALR,
  // S-type
  SB, SH, SW,
  // B-type
  BEQ, BNE, BLT, BGE, BLTU, BGEU,
  // U-type
  LUI, AUIPC,
  // J-type
  JAL
};

enum class TYPE { UNKNOWN, R_TYPE, I_TYPE, S_TYPE, B_TYPE, U_TYPE, J_TYPE };

typedef struct Instruction {
  uint32_t instruction{};
  uint8_t opcode{}, funct3{}, funct7{}, rs1{}, rs2{}, rd{};
  int32_t imm{};
  TYPE type = TYPE::UNKNOWN;
  OPERATION Operation = OPERATION::UNKNOWN;

} Instruction;
