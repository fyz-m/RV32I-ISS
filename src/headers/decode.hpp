#pragma once
#include "memory.hpp"

void decode(Instruction &instruction);

void decode_R_type(Instruction &fields);

void decode_I_type(Instruction &fields);

void decode_S_type(Instruction &fields);

void decode_B_type(Instruction &fields);

void decode_U_type(Instruction &fields);

void decode_J_type(Instruction &fields);

void extract_rd(Instruction &fields);

void extract_rs1(Instruction &fields);

void extract_rs2(Instruction &fields);

void extract_funct3(Instruction &fields);

void extract_funct7(Instruction &fields);

void extract_imm(Instruction &fields);

void extract_fields(Instruction &fields, bool rd = false, bool funct3 = false,
                    bool rs1 = false, bool rs2 = false, bool funct7 = false,
                    bool immediate = false);
