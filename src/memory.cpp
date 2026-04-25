#include <cstdint>
#include <array>

// Register File Class

// ignore writes to regfile[0]
// In RISC-V register x0 is hardwired to 0

// Method to write and read the register file
class RegisterFile
{
  private:
     std::array<uint32_t, 32> m_registers; // RISC-V architecture contains 32 registers
  public:
    
    // TODO: add error checking for out of bounds index
    void regWrite(uint32_t data, int address)
    {
      // Register x0 is hardwired to 0 so writes to the first register are ignored
      if (address == 0)
        return;

      m_registers[address] = data;
    }

    uint32_t regRead(int address)
    {
      if (address == 0)
        return 0;

      return m_registers[address];
    }
    
    
};



// Memory Class (32-bit so max 4GB)
// Method to write and read