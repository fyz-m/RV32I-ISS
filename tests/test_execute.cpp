#include "gtest/gtest.h"
#include <cstdint>
#include "../src/headers/cpu.hpp"


struct RtypeCase_e {
    OPERATION operation;
    int32_t expected_rd_value; // expected value
    int32_t rs1_value; // value of operand 1
    int32_t rs2_value; // value of operand 2
    std::string test_name;
};

class Rtype_Execute_Test : public ::testing::TestWithParam<RtypeCase_e> {};

TEST_P(Rtype_Execute_Test, executes)
{
    RtypeCase_e tc = GetParam();

    CPU_test cpu;
    cpu.instruction_fields.type = TYPE::R_TYPE;
    cpu.instruction_fields.Operation = tc.operation;
    cpu.instruction_fields.rs1 = 1;
    cpu.instruction_fields.rs2 = 2;
    cpu.instruction_fields.rd = 3;

    cpu.writeReg(1, tc.rs1_value);
    cpu.writeReg(2, tc.rs2_value);

    cpu.Execute();

    EXPECT_EQ(cpu.readReg(3), tc.expected_rd_value);

}

INSTANTIATE_TEST_SUITE_P(R_TYPE, Rtype_Execute_Test,

    ::testing::Values(
      RtypeCase_e{OPERATION::ADD, 50,  25, 25, "add_basic"}
    ),

    [](const ::testing::TestParamInfo<RtypeCase_e>& info) {
      return info.param.test_name;
      }
);