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

      Rtype_Execute_Case{OPERATION::XOR, -1, -1, 0, "xor_case"},
      Rtype_Execute_Case{OPERATION::OR, -1, -0, -1, "or_case"},
      Rtype_Execute_Case{OPERATION::AND, -1, -1, -1, "and_case"},
      Rtype_Execute_Case{OPERATION::AND, -1, 0, 0, "and_case_2"},
      
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
      Rtype_Execute_Case{OPERATION::SRA, -2147483648, 0b11111, -1, "shift_right_arithmetic_max_2"},

      Rtype_Execute_Case{OPERATION::SLT, 20, 30, 1, "set_less_than_basic" },
      Rtype_Execute_Case{OPERATION::SLT, 1200, 500, 0, "set_less_than_basic_2"},
      Rtype_Execute_Case{OPERATION::SLT, 1, 1, 0, "set_less_than_equal_values"},
      Rtype_Execute_Case{OPERATION::SLT, -5, 0, 1, "set_less_than_negative_values"},
      Rtype_Execute_Case{OPERATION::SLT, -700, -1000, 0, "set_less_than_negative_values_2"},

      Rtype_Execute_Case{OPERATION::SLTU, 20, 30, 1, "set_less_than_u_basic" },
      Rtype_Execute_Case{OPERATION::SLTU, 1200, 500, 0, "set_less_than_u_basic_2"},
      Rtype_Execute_Case{OPERATION::SLTU, 1, 1, 0, "set_less_than_u_equal_values"},
      Rtype_Execute_Case{OPERATION::SLTU, -1, 0, 0, "set_less_than_u_negative_values"},
      Rtype_Execute_Case{OPERATION::SLTU, 0, -1, 1, "set_less_than_u_negative_values_2"},
      Rtype_Execute_Case{OPERATION::SLTU, 0x7FFFFFFF, static_cast<int32_t>(0x80000000), 1, "set_less_than_u_compares_as_unsigned"},
      Rtype_Execute_Case{OPERATION::SLTU, static_cast<int32_t>(0x80000000), static_cast<int32_t>(0x80000001), 1, "set_less_than_u_compares_as_unsigned_2"}
    ),

    [](const ::testing::TestParamInfo<Rtype_Execute_Case>& info) {
      return info.param.test_name;
      }
);


struct Utype_Execute_Case {
    OPERATION operation;
    int32_t imm;
    int32_t expected_rd_value; // expected value
    std::string test_name;
    uint32_t PC = 0;
};

class Utype_Execute_Test : public ::testing::TestWithParam<Utype_Execute_Case> {};

TEST_P(Utype_Execute_Test, executes)
{
    Utype_Execute_Case tc = GetParam();

    CPU_test cpu;
    cpu.instruction_fields.type = TYPE::U_TYPE;
    cpu.instruction_fields.Operation = tc.operation;
    cpu.instruction_fields.rd = 1;
    cpu.instruction_fields.imm = tc.imm;
    cpu.writePC(tc.PC);

    cpu.writeReg(1, 0xFFF); 

    cpu.Execute();

    
    auto rd = static_cast<int32_t>(cpu.readReg(1));
    EXPECT_EQ(rd, tc.expected_rd_value);

}

INSTANTIATE_TEST_SUITE_P(U_TYPE, Utype_Execute_Test,

    ::testing::Values(

      Utype_Execute_Case{OPERATION::LUI, 0x8CDEF, static_cast<int32_t>(0x8CDEF000), "lui_basic"},
      Utype_Execute_Case{OPERATION::LUI, 0xFFFFF, static_cast<int32_t>(0xFFFFF000), "lui_max"},

      Utype_Execute_Case{OPERATION::AUIPC, 0xABCDE, static_cast<int32_t>(0xABCDE001), "auipc_basic", 0x001},
      Utype_Execute_Case{OPERATION::AUIPC, 0xFFFFF, static_cast<int32_t>(0xFFFFFFFF), "auipc_max", 0xFFF}
    ),

    [](const ::testing::TestParamInfo<Utype_Execute_Case>& info) {
      return info.param.test_name;
      }
);

TEST(Jtype_execute_test, test_JAL)
{
    int32_t jump_target_address{200};

    CPU_test cpu;
    cpu.instruction_fields.type = TYPE::J_TYPE;
    cpu.instruction_fields.Operation = OPERATION::JAL;
    cpu.instruction_fields.rd = 1;
    cpu.instruction_fields.imm =  jump_target_address;

    cpu.writePC(400);
    cpu.Execute();

    EXPECT_EQ(cpu.readReg(1), 404);
    EXPECT_EQ(cpu.readPC(), 600);

}

TEST(Jtype_execute_test, test_JAL_2)
{
    int32_t jump_target_address{0xA67F8};

    CPU_test cpu;
    cpu.instruction_fields.type = TYPE::J_TYPE;
    cpu.instruction_fields.Operation = OPERATION::JAL;
    cpu.instruction_fields.rd = 1;
    cpu.instruction_fields.imm =  jump_target_address;

    cpu.writePC(0x0000540C);
    cpu.Execute();

    EXPECT_EQ(cpu.readReg(1), 0x00005410);
    EXPECT_EQ(cpu.readPC(), 0x000ABC04);

}

TEST(Jtype_execute_test, test_JAL_max)
{
    int32_t jump_target_address{1048574};

    CPU_test cpu;
    cpu.instruction_fields.type = TYPE::J_TYPE;
    cpu.instruction_fields.Operation = OPERATION::JAL;
    cpu.instruction_fields.rd = 1;
    cpu.instruction_fields.imm =  jump_target_address;

    cpu.writePC(400);
    cpu.Execute();

    EXPECT_EQ(cpu.readReg(1), 404);
    EXPECT_EQ(cpu.readPC(), 1048974);

}

TEST(Jtype_execute_test, test_JAL_negative_max)
{
    int32_t jump_target_address{-1048576};

    CPU_test cpu;
    cpu.instruction_fields.type = TYPE::J_TYPE;
    cpu.instruction_fields.Operation = OPERATION::JAL;
    cpu.instruction_fields.rd = 1;
    cpu.instruction_fields.imm =  jump_target_address;

    cpu.writePC(0xFFFFFFFA);
    cpu.Execute();

    EXPECT_EQ(cpu.readReg(1), 0xFFFFFFFE);
    EXPECT_EQ(cpu.readPC(), static_cast<uint32_t>(4293918714));

}