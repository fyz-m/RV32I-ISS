#include "headers/decode.hpp"
#include "headers/memory.hpp"
#include <iostream>

void decode(Instruction &instruction) {

  instruction.opcode = instruction.instruction & 0x0000007F;

  switch (instruction.opcode) {
  case 51:
    decode_R_type(instruction);
    break;

  case (19 | 3 | 103):
    decode_I_type(instruction);
    break;

  case 35:
    decode_S_type(instruction);
    break;

  case 99:
    decode_B_type(instruction);
    break;

  case (55 | 23):
    decode_U_type(instruction);
    break;

  case (111):
    decode_J_type(instruction);
    break;

  default:
    std::cerr << "Unable to resolve instruction type" << std::endl;
  }
}

void decode_R_type(Instruction &fields) {
  // extract fields
  fields.rd = (fields.instruction >> 7) & 0x000001F;
  fields.funct3 =
      (fields.instruction >> 12) & 0x00007; // 0b0000'0000'0000'0000'0111
  fields.rs1 = (fields.instruction >> 15) & 0x0001F; // 0b0000'0000'0000'1111'1
  fields.rs2 = (fields.instruction >> 20) & 0x01F;   // 0b0000'0001'1111
  fields.funct7 = (fields.instruction >> 25);

  // Set operation
  switch (fields.funct3) {
  case 0b000:
    fields.Operation = (fields.funct7 == 0) ? OPERATION::ADD : OPERATION::SUB;
  }
}

void decode_I_type(Instruction &fields) {
  fields.rd = (fields.instruction >> 7) & 0x000F;
}

void decode_S_type(Instruction &fields) {
  fields.rd = (fields.instruction >> 7) & 0x000F;
}

void decode_B_type(Instruction &fields) {
  fields.rd = (fields.instruction >> 7) & 0x000F;
}

void decode_U_type(Instruction &fields) {
  fields.rd = (fields.instruction >> 7) & 0x000F;
}

void decode_J_type(Instruction &fields) {
  fields.rd = (fields.instruction >> 7) & 0x000F;
}