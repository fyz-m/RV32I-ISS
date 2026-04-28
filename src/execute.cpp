#include "headers/execute.hpp"
#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include <cstdint>

void execute(CPU &CPU, Memory *Data_Memory, Instruction *i) {
  Data_Memory->Write(static_cast<uint8_t>(32), 20);
  switch (i->Operation) {

  case OPERATION::ADD: {
    auto operand1 = static_cast<int32_t>(CPU.Reg_read(i->rs1));
    auto operand2 = static_cast<int32_t>(CPU.Reg_read(i->rs2));
    auto sum = operand1 + operand2;
    CPU.Reg_write(sum, i->rd);
    break;
  }

  case OPERATION::SUB:

    break;

  case OPERATION::UNKNOWN:

    break;
  }
}