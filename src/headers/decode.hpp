#pragma once
#include "memory.hpp"
#include <cstdint>

void decode(Instruction* instruction);

void decode_R_type(Instruction* instruction);

void decode_I_type(Instruction* instruction);

void decode_S_type(Instruction* instruction);

void decode_B_type(Instruction* instruction);

void decode_U_type(Instruction* instruction);

void decode_J_type(Instruction* instruction);