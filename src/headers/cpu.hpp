#pragma  once
#include "memory.hpp"
#include <cstdint>
#include <memory>


/*
  A CPU CORE "has-a" register file, pc, decoding and execution units
  TODO:

  - Move decoding logic inside 
    - Seperate decoder Class

  - Move execution logic inside
    - Seperate execution Class

  - Move Step function inside ( fetch/decode/execute loop)

  - Constructor functions takes as input parameters pointers to Memory objects (RAM + Instruction memory)
  - Default constructor initializes its own memory
    
*/ 
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

typedef struct  DecodedInstruction {

  uint32_t raw_inst;
  uint8_t opcode{}, funct3{}, funct7{}, rs1{}, rs2{}, rd{};
  int32_t imm{};
  TYPE type = TYPE::UNKNOWN;
  OPERATION Operation = OPERATION::UNKNOWN;

} Decoded_Instruction;



class CPU
{
  private:

    // Contains currently executing instruction
    uint32_t instruction_register;

    // Contains instruction fields (opcode, rs1, rd etc.)
    DecodedInstruction instruction_fields;

    // Program Counter: Contains memory address of instruction to execute
    uint32_t program_counter;

    // Register file: stores operands to perform operations on 
    RegisterFile register_file;

    // Memory containing instructions 
    std::shared_ptr <Memory> Instruction_Memory;

    // Memory for data
    std::shared_ptr <Memory> Data_Memory;

  public:

    CPU(int width = 32, std::shared_ptr<Memory> Instruction_Memory_ptr = nullptr, std::shared_ptr<Memory> Data_Memory_ptr = nullptr);
    
    void Step();

    int32_t readReg(int address) const;

    uint32_t readPC() const;
    
  // prviate:

    // Fetch instruction at address[PC] and write it to the instruction register
    void Fetch();

    // Decode the instruction, determining the operation to perform and the operands
    void Decode();

    // Execute the operation
    void Execute();

    void writePC(uint32_t data);
    
    void incrementPC();
    
    void writeReg(int address, int32_t data);
  

};





