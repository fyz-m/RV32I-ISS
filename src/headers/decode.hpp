#pragma once
#include "cpu.hpp"

  void decode(DecodedInstruction &input_instruction);

  void decode_R_type(DecodedInstruction& fields);

  void decode_I_type(DecodedInstruction& fields);

  void decode_S_type(DecodedInstruction& fields);

  void decode_B_type(DecodedInstruction& fields);

  void decode_U_type(DecodedInstruction& fields);

  void decode_J_type(DecodedInstruction& fields);

  void extract_rd(DecodedInstruction& fields);

  void extract_rs1(DecodedInstruction& fields);

  void extract_rs2(DecodedInstruction& fields);

  void extract_funct3(DecodedInstruction& fields);

  void extract_funct7(DecodedInstruction& fields);

  void extract_imm(DecodedInstruction& fields);

  void extract_R_type(DecodedInstruction& fields);

  void extract_I_type(DecodedInstruction& fields);

  void extract_S_type(DecodedInstruction& fields);

  void extract_B_type(DecodedInstruction& fields);

  void extract_U_type(DecodedInstruction& fields);

  void extract_J_type(DecodedInstruction& fields);

  void set_type(DecodedInstruction& fields);