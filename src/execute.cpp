#include "headers/execute.hpp"
#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include <cstdint>

void execute(CPU &CPU, Memory *Data_Memory, Instruction &i) {
  Data_Memory->Write(static_cast<uint8_t>(32), 20);

  switch (i.Operation) {

  case OPERATION::ADD:
  case OPERATION::SUB: {

    auto operand1 = (CPU.Reg_read(i.rs1));
    auto operand2 = (CPU.Reg_read(i.rs2));

    auto sum = (i.Operation == OPERATION::ADD) ? (operand1 + operand2)
                                               : (operand1 - operand2);
    CPU.Reg_write(sum, i.rd);
    break;
  }
  case OPERATION::ADDI: {
    auto sum = (CPU.Reg_read(i.rs1)) + i.imm;
    CPU.Reg_write(sum, i.rd);
    break;
  }
    default:
      break;
  }
}