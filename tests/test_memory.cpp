#include "gtest/gtest.h"
#include "../src/headers/memory.hpp"

class Registerfile_test : public ::testing::Test 
{
  protected:

    void SetUp() override 
    {
     rf = new RegisterFile(32);
    }

    void TearDown() override
    {
      delete rf;
    }

    RegisterFile* rf;
};

TEST_F(Registerfile_test, can_write_and_read_registers)
{
  rf->Write(5, 50);
  ASSERT_EQ(50, rf->Read(5));

  rf->Write(5, 0);
  ASSERT_EQ(0, rf->Read(5));

  rf->Write(31, 0xFFFFFFFF);
  ASSERT_EQ(0xFFFFFFFF, rf->Read(31));
}

TEST_F(Registerfile_test, register0_is_wired_to_zero)
{
  ASSERT_EQ(0, rf->Read(0));
}

TEST_F(Registerfile_test, writes_to_reg0_are_ignored)
{
  rf->Write(0, 500);
  ASSERT_EQ(0, rf->Read(0));

  rf->Write(0, -1);
  ASSERT_EQ(0, rf->Read(0));
}

TEST_F(Registerfile_test, throws_exception_on_invalid_register_index)
{
  ASSERT_ANY_THROW(rf->Write(-1, 0));
  ASSERT_ANY_THROW(rf->Write(32, 0));

  ASSERT_ANY_THROW(rf->Read(-1));
  ASSERT_ANY_THROW(rf->Read(32));
}