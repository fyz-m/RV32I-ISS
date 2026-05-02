#include "gtest/gtest.h"
#include <cstdint>
#include <sys/types.h>
#include "../src/headers/decode.hpp"




// TEST(Decode_S_type_Test, registers) {
//   // Check if immediate gets extracted and assembled properly

//   DecodedInstruction fields {};

//   fields.raw_inst = 0x19488823; // sb x20, 400(x17)
//   decode(fields);

//   EXPECT_EQ(fields.rs2, 20);
//   EXPECT_EQ(fields.rs1, 17);

// }

// TEST(Decode_S_type_Test, IMM) {
//   // Check if immediate gets extracted and assembled properly

//   DecodedInstruction fields {};

//   fields.raw_inst = 0x19488823; // sb x20, 400(x17)
//   decode(fields);

//   EXPECT_EQ(fields.imm, 400);

// }


struct RtypeCase {
    uint32_t instruction;
    uint8_t expected_rd, expected_rs1, expected_rs2;
    OPERATION expected_op; 
    std::string test_name;
};

class RtypeTest : public ::testing::TestWithParam<RtypeCase> {};

TEST_P(RtypeTest, decode_R_type_instructions)
{
    RtypeCase tc = GetParam();

    DecodedInstruction fields;
    fields.raw_inst = tc.instruction;
    
    decode(fields);

    EXPECT_EQ(fields.rd, tc.expected_rd);
    EXPECT_EQ(fields.rs1, tc.expected_rs1);
    EXPECT_EQ(fields.rs2, tc.expected_rs2);
    EXPECT_EQ(fields.Operation, tc.expected_op);
}

INSTANTIATE_TEST_SUITE_P(R_TYPE_DECODE_TEST, RtypeTest,

    ::testing::Values(
      RtypeCase {0x003100b3, 1, 2, 3, OPERATION::ADD, "add_basic"},  // add x1, x2, x3
      RtypeCase {0x403100b3, 1, 2, 3 , OPERATION::SUB, "sub_basic"} // sub x1, x2, x3
    ),

    [](const ::testing::TestParamInfo<RtypeCase>& info) {
      return info.param.test_name;
      }
);


struct ItypeCase {
    uint32_t instruction;
    uint8_t expected_rd, expected_rs1; 
    int32_t expected_imm;
    OPERATION expected_op;
    std::string test_name; 
};

class ItypeTest : public ::testing::TestWithParam<ItypeCase> {};

TEST_P(ItypeTest, decode_I_type_instructions)
{
    ItypeCase tc = GetParam();

    DecodedInstruction fields;
    fields.raw_inst = tc.instruction;

    decode(fields);

    EXPECT_EQ(fields.rd, tc.expected_rd);
    EXPECT_EQ(fields.rs1, tc.expected_rs1);
    EXPECT_EQ(fields.imm, tc.expected_imm) << "Incorrect immediate extraction (may not be properly sign extended)";
    EXPECT_EQ(fields.Operation, tc.expected_op);
}

INSTANTIATE_TEST_SUITE_P(I_TYPE_DECODE_TEST, ItypeTest,

    ::testing::Values(
      ItypeCase {0x02810093, 1, 2, 40, OPERATION::ADDI, "addi_basic"},  // addi x1, x2, 40
      ItypeCase {0x00028503, 10, 5, 0 , OPERATION::LB, "lb_basic"}, // lb x10, 0(x5)
      // Testing immediate sign ext
      ItypeCase {0xfec10093, 1, 2, -20, OPERATION::ADDI, "sign_ext"},  // addi x1, x2, -20
      ItypeCase {0xfff10093, 1, 2, -1, OPERATION::ADDI, "sign_ext_max"} // addi x1, x2, -1
    ),

    [](const ::testing::TestParamInfo<ItypeCase>& info) {
      return info.param.test_name;
      }
);