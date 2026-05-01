#include "headers/cpu.hpp"
#include "headers/memory.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <ostream>



int main() {

  std::shared_ptr <Memory> I = std::make_shared <Memory>();
  std::shared_ptr <Memory> D = std::make_shared <Memory>();

 
  CPU cpu (32, I, D);
  
} 

