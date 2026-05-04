#include "gtest/gtest.h"
#include <cstdint>
#include "../src/headers/cpu.hpp"


struct Rtype_Execute_Case {
    OPERATION operation;
    int32_t rs1_value; // value of operand 1
    int32_t rs2_value; // value of operand 2
    int32_t expected_rd_value; // expected value
    std::string test_name;
};

class Rtype_Execute_Test : public ::testing::TestWithParam<Rtype_Execute_Case> {};

TEST_P(Rtype_Execute_Test, executes)
{
    Rtype_Execute_Case tc = GetParam();

    CPU_test cpu;
    cpu.instruction_fields.type = TYPE::R_TYPE;
    cpu.instruction_fields.Operation = tc.operation;
    cpu.instruction_fields.rs1 = 1;
    cpu.instruction_fields.rs2 = 2;
    cpu.instruction_fields.rd = 3;

    cpu.writeReg(1, tc.rs1_value);
    cpu.writeReg(2, tc.rs2_value);

    cpu.Execute();
    auto rd = static_cast<int32_t>(cpu.readReg(3));
    EXPECT_EQ(rd, tc.expected_rd_value);

}

INSTANTIATE_TEST_SUITE_P(R_TYPE, Rtype_Execute_Test,

    ::testing::Values(
      Rtype_Execute_Case{OPERATION::ADD, 25,  25, 50, "add_basic"},
      Rtype_Execute_Case{OPERATION::ADD, 0,  -1, -1, "add_negative_number"},
      Rtype_Execute_Case{OPERATION::ADD, -300,  -700, -1000, "add_negative_numbers"},
      Rtype_Execute_Case{OPERATION::ADD,  2147483647, 1, -2147483648, "add_positive_overflow"},
      Rtype_Execute_Case{OPERATION::ADD,  -2147483648, -1, 2147483647, "add_negative_overflow"},

      Rtype_Execute_Case{OPERATION::SUB, 100,  25, 75, "sub_basic"},
      Rtype_Execute_Case{OPERATION::SUB, 200,  -200, 400, "sub_negative_number"},
      Rtype_Execute_Case{OPERATION::SUB, -300,  -700, 400, "sub_negative_numbers"},
      Rtype_Execute_Case{OPERATION::SUB,  2147483647, -1, -2147483648, "sub_positive_overflow"},
      Rtype_Execute_Case{OPERATION::SUB,  -2147483648, 1, 2147483647, "sub_negative_overflow"},
      
      Rtype_Execute_Case{OPERATION::SLL, 2, 2, 8, "shift_left_logical_basic"},
      Rtype_Execute_Case{OPERATION::SLL, 1, 1, 2, "shift_left_logical_fills_leading_bits_with_zero"},
      Rtype_Execute_Case{OPERATION::SLL, 2147483647, 0b11111, -2147483648, "shift_left_logical_max"},
      Rtype_Execute_Case{OPERATION::SLL, 1, 0b11111, -2147483648, "shift_left_logical_max_2"},

      Rtype_Execute_Case{OPERATION::SRL, 8, 2, 2, "shift_right_logical_basic"},
      Rtype_Execute_Case{OPERATION::SRL, -1, 1, 0x7FFFFFFF, "shift_right_logical_does_not_signext"},
      Rtype_Execute_Case{OPERATION::SRL, 2147483647, 0b11111, 0, "shift_right_logical_max"},
      Rtype_Execute_Case{OPERATION::SRL, -2147483648, 0b11111, 1, "shift_right_logical_max_2"},

      Rtype_Execute_Case{OPERATION::SRA, 8, 2, 2, "shift_right_arithmetic_basic"},
      Rtype_Execute_Case{OPERATION::SRA, -8, 2, -2, "shift_right_arithmetic_negative"},
      Rtype_Execute_Case{OPERATION::SRA, -1, 3, -1, "shift_right_arithmetic_does_signext"},
      Rtype_Execute_Case{OPERATION::SRA, 2147483647, 0b11111, 0, "shift_right_arithmetic_max"},
      Rtype_Execute_Case{OPERATION::SRA, -2147483648, 0b11111, -1, "shift_right_arithmetic_max_2"}
    ),

    [](const ::testing::TestParamInfo<Rtype_Execute_Case>& info) {
      return info.param.test_name;
      }
);