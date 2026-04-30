#include "headers/cpu.hpp"
#include "headers/decode.hpp"
#include "headers/execute.hpp"
#include "headers/memory.hpp"
#include <cstdint>
#include <iostream>
#include <ostream>



int main() {

  
  // Create CPU object with register file + pc
  CPU cpu;


  //  TEST
  ///////////////////////////////////////////////
  uint32_t inst = 0x00a10093;
  ///////////////////////////////////////////////
  

  std::cout << "Instruction :";
  std::cout << std::hex << "" << std::endl;
  std::cout << "register x1 :";
  std::cout << std::dec << "" << std::endl;

  



