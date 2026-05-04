#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include "headers/decode.hpp"
#include <cstdint>
#include <memory>

// TODO:
// Change instruction_fields.raw_inst to be a pointer to the instruction register
// To prevent unneccesary copying each time instruction is fetched

  CPU::CPU(int width, 
           std::shared_ptr<Memory> Instruction_Memory_ptr, 
           std::shared_ptr<Memory> Data_Memory_ptr) 
           
    : instruction_register{}, instruction_fields{}, program_counter{},
      register_file(width), 
      Instruction_Memory(Instruction_Memory_ptr), 
      Data_Memory(Data_Memory_ptr)
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
    switch (instruction_fields.type) 
    {
      case TYPE::R_TYPE: 
        execute_R_type();
        return;
        
      case TYPE::I_TYPE:
        execute_I_type();
        return;        

      case TYPE::S_TYPE:
        execute_S_type();
        return;
              
      case TYPE::B_TYPE:
        execute_B_type();
        return;

      case TYPE::U_TYPE:
        execute_U_type();
        return;

      case TYPE::J_TYPE:
        execute_J_type();
        return;

      case TYPE::UNKNOWN:
        return;
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

  void CPU::writeReg(int address, uint32_t data) 
  {
    register_file.Write(address, data);
  }

  uint32_t CPU::readReg(int address) const 
  { 
    return register_file.Read(address); 
  }


  void CPU::execute_R_type()
  {
    // All R-type instructions operate on two operands from the register file specified at location rs1 and rs2
    // result is written to register file at location rd
    auto rs1 = static_cast<int32_t>((readReg(instruction_fields.rs1)));
    auto rs2 = static_cast<int32_t>((readReg(instruction_fields.rs2)));
    auto &rd = instruction_fields.rd;
    int32_t result {};   

    switch (instruction_fields.Operation) 
    {
      case OPERATION::ADD:
        result = rs1 + rs2;
        break;

      case OPERATION::SUB:
        result = rs1 - rs2;
        break;
            
      default: 
        break; 
    }

    // Write result back to register rd
    writeReg(rd, result);
  }

  void CPU::execute_I_type()
  {
    // All I-type instructions operate on immediate and an operand specified at location rs1 of registerfile
    //   - Except load instructions
    // result is written to register file at location rd
    auto rs1 = (readReg(instruction_fields.rs1));
    auto &imm = instruction_fields.imm;
    int32_t result {};
      
    switch (instruction_fields.Operation) 
    {
      case OPERATION::ADDI:
        result = rs1 + imm;
        break;

      case OPERATION::LB:
        result = Data_Memory->Read_Byte(imm + rs1);
        break;
            
      default: 
        break; 

    }

    // Write result back to register rd
    writeReg(instruction_fields.rd, result);
    return;
  }

  void CPU::execute_S_type()
  {
    // Memory address to store value in rs2 = value in rs1 + imm
    int address = readReg(instruction_fields.rs1) + instruction_fields.imm;
    uint32_t rs2 = readReg(instruction_fields.rs2);

    switch (instruction_fields.Operation) 
    {
            
      case OPERATION::SB:
        // Store first 2 bytes of rs2
        Data_Memory->Write(static_cast<uint8_t>(rs2), address);
        return;

      case OPERATION::SH:
        // Store first 4 bytes of rs2
        Data_Memory->Write(static_cast<uint16_t>(rs2), address);
        return;

      case OPERATION::SW:
        // Store rs2
        Data_Memory->Write(rs2, address);
        return;

       default: 
         return; 
    }      
  }

  void CPU::execute_B_type()
  {

  }

  void CPU::execute_U_type()
  {

  }

  void CPU::execute_J_type()
  {

  }
