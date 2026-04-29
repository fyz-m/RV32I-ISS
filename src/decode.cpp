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

  fields.rd = extract_rd(fields.instruction);
  fields.funct3 = extract_funct3(fields.instruction);
  fields.rs1 = extract_rs1(fields.instruction);
  fields.rs2 = extract_rs2(fields.instruction);
  fields.funct7 = extract_funct7(fields.instruction);
  // Set operation
  switch (fields.funct3) {
  case 0b000:
    fields.Operation = (fields.funct7 == 0) ? OPERATION::ADD : OPERATION::SUB;
  }
}

void decode_I_type(Instruction &fields) {
  fields.rd = (fields.instruction >> 7) & 0x000F;
  fields.funct3 = (fields.instruction >> 12) & 0x00007;
  fields.rs1 = (fields.instruction >> 15) & 0x0001F;
  fields.imm = fields.instruction >> 20;
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

uint8_t extract_rd(uint32_t &instruction) {
  // Extract the destination register from an instruction
  return (instruction >> 7) & 0x000F;
}

uint8_t extract_rs1(uint32_t &instruction) {
  // Extract the first source register from an instruction
  return (instruction >> 15) & 0x0001F;
}

uint8_t extract_rs2(uint32_t &instruction) {
  // Extract the second source register from an instruction
  return (instruction >> 20) & 0x01F;
}

uint8_t extract_funct3(uint32_t &instruction) {
  // Extract the 3-bit function field from an instruction
  return (instruction >> 12) & 0x00007;
}

uint8_t extract_funct7(uint32_t &instruction) {
  // Extract the 7-bit function field from an instruction
  return instruction >> 25;
}