#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <ostream>

void Test(CPU &cpu, std::shared_ptr <Memory> I, std::shared_ptr <Memory> D);

int main() {

  std::shared_ptr <Memory> I = std::make_shared <Memory>();
  std::shared_ptr <Memory> D = std::make_shared <Memory>();

 
  CPU cpu (32, I, D);

  Test(cpu, I, D);

  

} 

void Test(CPU &cpu, std::shared_ptr <Memory> I, std::shared_ptr <Memory> D)
{
  
  uint32_t inst = 0x003100b3; // add x1, x2, x3
  I->Write(inst, 0);

  cpu.writeReg(3, 10);
  cpu.writeReg(2, 10);
  cpu.Step();

  std::cout <<  "add x2, x2, x3" << std::endl;
  std::cout << "Instruction = ";
  std::cout << std::hex << I->Read_Word(0) << "   ";
  std::cout << "Expected = ";
  std::cout << std::hex << inst << std::endl;
  std::cout << "register x1 = ";
  std::cout << std::dec << cpu.readReg(1) << "   ";
  std::cout << "Expected = ";
  std::cout << std::dec << "20" << std::endl;
  std::cout << std::endl;


  inst = 0x403100b3; // sub x1, x2, x3
  I->Write(inst, 0);

  cpu.writeReg(2, 20);
  cpu.writeReg(3, 5);
  cpu.Step();
  
  std::cout <<  "sub x1, x2, x3" << std::endl;
  std::cout << "Instruction = ";
  std::cout << std::hex << I->Read_Word(0) << "   ";
  std::cout << "Expected = ";
  std::cout << std::hex << inst << std::endl;

  std::cout << "register x1 = ";
  std::cout << std::dec << cpu.readReg(1) << "   ";
  std::cout << "Expected = ";
  std::cout << std::dec << "15" << std::endl;

  cpu.writeReg(2, 10);
  cpu.writeReg(3, 20);
  cpu.Step();

  std::cout << "register x1 = ";
  std::cout << std::dec << cpu.readReg(1) << "   ";
  std::cout << "Expected = ";
  std::cout << std::dec << "-10" << std::endl;
  std::cout << std::endl;


  inst = 0x02810093; // addi x1, x2, 40
  I->Write(inst, 0);

  cpu.writeReg(2, 20);
  cpu.Step();

  std::cout <<  "addi x1, x2, 20" << std::endl;
  std::cout << "Instruction = ";
  std::cout << std::hex << I->Read_Word(0) << "   ";
  std::cout << "Expected = ";
  std::cout << std::hex << inst << std::endl;
  std::cout << "register x1 = ";
  std::cout << std::dec << cpu.readReg(1) << "   ";
  std::cout << "Expected = ";
  std::cout << std::dec << "60" << std::endl;
  std::cout << std::endl;


  inst = 0x00028503; // lb x10, 0(x5)
  I->Write(inst, 0);
  D->Write(static_cast<uint8_t>(0xFF), 7);
  cpu.writeReg(5, 7);
  cpu.Step();

  std::cout <<  "lb x10, 0(x5)" << std::endl;
  std::cout << "Instruction = ";
  std::cout << std::hex << I->Read_Word(0) << "   ";
  std::cout << "Expected = ";
  std::cout << std::hex << inst << std::endl;

  std::cout << "register x10 = ";
  std::cout << std::hex << cpu.readReg(10) << "   ";
  std::cout << "Expected = ";
  std::cout << "FF" << std::endl;
  std::cout << std::endl;

}

