#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include "headers/decode.hpp"
#include <cstdint>

  CPU::CPU(int) 
    : program_counter{}, register_file() 
    {}


  void CPU::Step()
  {
    Fetch();
    Decode();
    Execute();

  }

  void CPU::Fetch()
  {
    instruction_register = Instruction_Memory->Read_Word(program_counter);
    instruction_fields.raw_inst = instruction_register;
  }

  void CPU::Decode()
  {
    decode(instruction_fields);
  }

  void CPU::Execute()
  {
    DecodedInstruction &i = instruction_fields;
    
    switch (i.type) 
    {
    
      case TYPE::R_TYPE: 
        {
          // All R-type instructions operate on two operands from the register file specified at location rs1 and rs2
          // result is written to register file at location rd
          auto operand1 = (readReg(i.rs1));
          auto operand2 = (readReg(i.rs2));
          int32_t result {};

          switch (i.Operation) 
          {
            case OPERATION::ADD:
                 result = operand1 + operand2;
                 break;

            case OPERATION::SUB:
                 result = operand1 - operand2;
                 break;
            
            default: break; 
          }
          // Write result back to register rs2
          writeReg(i.rs2, result);
          break;
        }

        
      case TYPE::I_TYPE:
        {
          // All I-type instructions operate on immediate and an operand specified at location rs1 of registerfile
          //   - Except load instructions
          // result is written to register file at location rd
          auto rs1 = (readReg(i.rs1));
          auto imm = i.imm;
          int32_t result {};
      

          switch (i.Operation) 
          {
            case OPERATION::ADDI:
                 result = rs1 + imm;
                 break;

            case OPERATION::LB:
                 result = Data_Memory->Read_Byte(imm + rs1);
                 break;
            
            default: break; 
          }

          // Write result back to register rs2
          writeReg(i.rs2, result);
          break;
        }

      case TYPE::S_TYPE:
      case TYPE::B_TYPE:
      case TYPE::U_TYPE:
      case TYPE::J_TYPE:
      case TYPE::UNKNOWN:
      break;
     }
    }
  

  void CPU::writePC(uint32_t data) 
  {
    // Write to the PC for branch and jump instructions
    program_counter = data;
  }

  void CPU::incrementPC(void) 
  {
    program_counter += 4; 
  }

  uint32_t CPU::readPC(void) const
  { 
    return program_counter; 
  }

  void CPU::writeReg (int address, int32_t data) 
  {
    register_file.Write(address, data);
  }

  int32_t CPU::readReg(int address) const 
  { 
    return register_file.Read(address); 
  }
