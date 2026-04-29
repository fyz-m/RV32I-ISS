#pragma once
#include "memory.hpp"

void decode(Instruction &instruction);

void decode_R_type(Instruction &fields);

void decode_I_type(Instruction &fields);

void decode_S_type(Instruction &fields);

void decode_B_type(Instruction &fields);

void decode_U_type(Instruction &fields);

void decode_J_type(Instruction &fields);