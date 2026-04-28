#include "headers/decode.hpp"
#include <iostream>


void decode(Instruction* instruction) {
  
  instruction->opcode = instruction->instruction & 0x000FF;

  switch (instruction->opcode) {
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

void decode_R_type(Instruction* instruction)
{
  
}

void decode_I_type(Instruction* instruction)
{
  
}

void decode_S_type(Instruction* instruction)
{
  
}

void decode_B_type(Instruction* instruction)
{
  
}

void decode_U_type(Instruction* instruction)
{
  
}

void decode_J_type(Instruction* instruction)
{
  
}