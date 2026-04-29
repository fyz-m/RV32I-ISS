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
  extract_fields(fields, true, true, true, true, true);

  switch (fields.funct3) {
  case 0:
    fields.Operation = (fields.funct7 == 0) ? OPERATION::ADD : OPERATION::SUB;
  }
}

void decode_I_type(Instruction &fields) {

  extract_fields(fields, true, true, true, true, true, true);

  switch (fields.funct3) {
  case 0:
    fields.Operation = (fields.opcode == 19) ? OPERATION::ADDI : OPERATION::LB;    
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
    break;
  }
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

void extract_fields(Instruction &fields, bool rd, bool funct3, bool rs1,
                    bool rs2, bool funct7, bool immediate) {
  if (rd)
     extract_rd(fields);
  if (funct3)
     extract_funct3(fields);
  if (rs1)
     extract_rs1(fields);
  if (rs2)
     extract_rs2(fields);
  if (funct7)
    extract_funct7(fields);
  if (immediate)
     extract_imm(fields);
}

void extract_rd(Instruction &fields) {
  // Extract the destination register from an instruction
  fields.rd = (fields.instruction >> 7) & 0x000F;
}

void extract_rs1(Instruction &fields) {
  // Extract the first source register from an instruction
  fields.rs1 = (fields.instruction >> 15) & 0x0001F;
}

void extract_rs2(Instruction &fields) {
  // Extract the second source register from an instruction
  fields.rs2 = (fields.instruction >> 20) & 0x01F;
}

void extract_funct3(Instruction &fields) {
  // Extract the 3-bit function field from an instruction
  fields.funct3 = (fields.instruction >> 12) & 0x00007;
}

void extract_funct7(Instruction &fields) {
  // Extract the 7-bit function field from an instruction
  fields.funct7 = fields.instruction >> 25;
}

void extract_imm(Instruction &fields) {

  switch (fields.type) {

  case TYPE::I_TYPE:
    fields.imm =  fields.instruction >> 20;
    break;

  case TYPE::S_TYPE:
    break;

  case TYPE::B_TYPE:
    break;

  case TYPE::U_TYPE:
    break;

  case TYPE::J_TYPE:
    break;
    
  default:
    break;
  }
}