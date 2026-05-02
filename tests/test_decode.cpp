#include "gtest/gtest.h"
#include <cstdint>
#include <sys/types.h>
#include "../src/headers/decode.hpp"


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

struct StypeCase {
    uint32_t instruction;
    uint8_t expected_rs2; 
    int32_t expected_imm;
    uint8_t expected_rs1;
    OPERATION expected_op;
    std::string test_name; 
};

class StypeTest : public ::testing::TestWithParam<StypeCase> {};

TEST_P(StypeTest, decode_S_type_instructions)
{
    StypeCase tc = GetParam();

    DecodedInstruction fields;
    fields.raw_inst = tc.instruction;

    decode(fields);

    EXPECT_EQ(fields.rs1, tc.expected_rs1);
    EXPECT_EQ(fields.rs2, tc.expected_rs2);
    EXPECT_EQ(fields.imm, tc.expected_imm) << "Incorrect immediate extraction (may not be properly sign extended)";
    EXPECT_EQ(fields.Operation, tc.expected_op);
}

INSTANTIATE_TEST_SUITE_P(S_TYPE_DECODE_TEST, StypeTest,

    ::testing::Values(
      StypeCase {0x19488823, 20, 400, 17, OPERATION::SB, "sb_basic" }, // sb x20, 400(x17)
      StypeCase {0x00a01023, 10, 0, 0, OPERATION::SH, "sh_basic" }, // sh x10, 0(x0)
      StypeCase {0x7e09a623, 0, 2028, 19, OPERATION::SW, "sw_basic" }, // sw x0, 2028(x19)

      StypeCase {0x80208023, 2, -2048, 1, OPERATION::SB, "sb_negative_imm" },  // sb x2, -2048(x1)
      StypeCase {0xfdf09723, 31, -50, 1, OPERATION::SH, "sh_negative_imm" },  // sh x31, -50(x1)
      StypeCase {0xfef6afa3, 15, -1, 13, OPERATION::SW, "sw_negative_imm" }   // sw x15, -1(x13)
    ),

    [](const ::testing::TestParamInfo<StypeCase>& info) {
      return info.param.test_name;
      }
);

struct BtypeCase {
    uint32_t instruction;
    uint8_t expected_rs1; 
    uint8_t expected_rs2;
    int32_t expected_imm;
    OPERATION expected_op;
    std::string test_name; 
};

class BtypeTest : public ::testing::TestWithParam<BtypeCase> {};

TEST_P(BtypeTest, decode_B_type_instructions)
{
    BtypeCase tc = GetParam();

    DecodedInstruction fields;
    fields.raw_inst = tc.instruction;

    decode(fields);

    EXPECT_EQ(fields.rs1, tc.expected_rs1);
    EXPECT_EQ(fields.rs2, tc.expected_rs2);
    EXPECT_EQ(fields.imm, tc.expected_imm) << "Incorrect immediate extraction (may not be properly sign extended)";
    EXPECT_EQ(fields.Operation, tc.expected_op);
}

INSTANTIATE_TEST_SUITE_P(B_TYPE_DECODE_TEST, BtypeTest,

    ::testing::Values(
      BtypeCase{0x014000e3, 0, 20, 2048, OPERATION::BEQ, "beq_basic"}, // beq x0, x20, 2048
      BtypeCase{0x00109663, 1,1, 12, OPERATION::BNE, "bne_basic"}, // bne x1, x1, 12
      BtypeCase{0x0010c663, 1,1, 12, OPERATION::BLT, "blt_basic"}, // blt x1, x1, 12
      BtypeCase{0x0010d663, 1,1, 12, OPERATION::BGE, "bge_basic"}, // bge x1, x1, 12
      BtypeCase{0x0010e663, 1,1, 12, OPERATION::BLTU, "bltu_basic"}, // bltu x1, x1, 12
      BtypeCase{0x0010f663, 1,1, 12, OPERATION::BGEU, "bgeu_basic"}, // bgeu x1, x1, 12
      
      // Immediate tests 
      BtypeCase{0xfe108ae3, 1,1, -12, OPERATION::BEQ, "imm_negative"}, // bge x1, x1, -12 
      BtypeCase{0x00108263, 1, 1, 4, OPERATION::BEQ, "imm_min_positive"}, // beq x1, x1, 4
      BtypeCase{0xfe108ee3, 1, 1, -4, OPERATION::BEQ, "imm_min_negative"}, // beq x1, x1, -4
      BtypeCase{0x81400063, 0, 20, -4096, OPERATION::BEQ, "imm_min"}, // beq x0, x20, -4096
      BtypeCase{0x7f400fe3, 0, 20, 4094, OPERATION::BEQ, "imm_max"} // beq x0, x20, 4094
      
    ),

    [](const ::testing::TestParamInfo<BtypeCase>& info) {
      return info.param.test_name;
      }
);




  
