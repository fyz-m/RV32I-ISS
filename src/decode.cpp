#include "headers/decode.hpp"
#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include <iostream>

void decode(DecodedInstruction &input_instruction) {

  
  input_instruction.opcode = input_instruction.raw_inst & 0x0000007F;

  switch (input_instruction.type) {
  case TYPE::R_TYPE:
    decode_R_type(input_instruction);
    break;

  case TYPE::I_TYPE:
    decode_I_type(input_instruction);
    break;

  case TYPE::S_TYPE:
    decode_S_type(input_instruction);
    break;

  case TYPE::B_TYPE:
    decode_B_type(input_instruction);
    break;

  case TYPE::U_TYPE:
    decode_U_type(input_instruction);
    break;

  case TYPE::J_TYPE:
    decode_J_type(input_instruction);
    break;

  default:
    std::cerr << "Unable to resolve instruction type" << std::endl;
  }
}


void decode_R_type(DecodedInstruction& fields) {
  // extract fields
  extract_R_type(fields);

  // Set operation
  switch (fields.funct3) {
  case 0:
    fields.Operation = (fields.funct7 == 0) ? OPERATION::ADD : OPERATION::SUB;
  }
}

void decode_I_type(DecodedInstruction& fields) {


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

void decode_S_type(DecodedInstruction& fields) {
  fields.rd = (fields.raw_inst >> 7) & 0x000F;
}

void decode_B_type(DecodedInstruction& fields) {
  fields.rd = (fields.raw_inst >> 7) & 0x000F;
}

void decode_U_type(DecodedInstruction& fields) {
  fields.rd = (fields.raw_inst >> 7) & 0x000F;
}

void decode_J_type(DecodedInstruction& fields) {
  fields.rd = (fields.raw_inst >> 7) & 0x000F;
}

void extract_R_type(DecodedInstruction& fields)
{
  extract_rd(fields);
  extract_funct3(fields);
  extract_rs1(fields);
  extract_rs2(fields);
  extract_funct7(fields);
}

void extract_I_type(DecodedInstruction& fields)
{
  extract_rd(fields);
  extract_funct3(fields);
  extract_rs1(fields);
  fields.imm = fields.raw_inst >> 20;
}

void extract_S_type(DecodedInstruction& fields)
{
  extract_funct3(fields);
  extract_rs1(fields);
  extract_rs2(fields);
}

void extract_B_type(DecodedInstruction& fields)
{
  // Same fields as S-type, immediate is encoded differently
  extract_S_type(fields);
}

void extract_U_type(DecodedInstruction& fields)
{
  extract_rd(fields);
}

void extract_J_type(DecodedInstruction& fields)
{
  // Same fields as U-type, immediate is encoded differently
  extract_U_type(fields);
}

void extract_rd(DecodedInstruction& fields) {
  // Extract the destination register from an instruction
  fields.rd = (fields.raw_inst >> 7) & 0x000F;
}

void extract_rs1(DecodedInstruction& fields) {
  // Extract the first source register from an instruction
  fields.rs1 = (fields.raw_inst >> 15) & 0x0001F;
}

void extract_rs2(DecodedInstruction& fields) {
  // Extract the second source register from an instruction
  fields.rs2 = (fields.raw_inst >> 20) & 0x01F;
}

void extract_funct3(DecodedInstruction& fields) {
  // Extract the 3-bit function field from an instruction
  fields.funct3 = (fields.raw_inst >> 12) & 0x00007;
}

void extract_funct7(DecodedInstruction& fields) {
  // Extract the 7-bit function field from an instruction
  fields.funct7 = fields.raw_inst >> 25;
}

void set_type(DecodedInstruction& fields)
{
  switch (fields.opcode) {
  case 51:
    fields.type = TYPE::R_TYPE; 
    break;

  case 19:
  case 3:
  case 103:
    fields.type = TYPE::I_TYPE;
    break;

  case 35:
    fields.type = TYPE::S_TYPE;
    break;

  case 99:
    fields.type = TYPE::B_TYPE;
    break;

  case 55:
  case 23:
    fields.type = TYPE::U_TYPE;
    break;

  case 111:
    fields.type = TYPE::J_TYPE;
    break;

  default:
    std::cerr << "Unable to resolve instruction type" << std::endl;
  }
}