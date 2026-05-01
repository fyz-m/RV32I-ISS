#include <gtest/gtest.h>
#include "../src/headers/decode.hpp"


TEST(Decode_R_type_Test, ADD) {

  DecodedInstruction fields {};

  fields.raw_inst = 0x003100b3; // add x1, x2, x3
  decode(fields);

  EXPECT_EQ(fields.rs1, 2);
  EXPECT_EQ(fields.rs2, 3);
  EXPECT_EQ(fields.rd, 1);
  EXPECT_EQ(fields.Operation, OPERATION::ADD);
}

TEST(Decode_R_type_Test, SUB) {

  DecodedInstruction fields {};

  fields.raw_inst = 0x403100b3; // sub x1, x2, x3
  decode(fields);

  EXPECT_EQ(fields.rs1, 2);
  EXPECT_EQ(fields.rs2, 3);
  EXPECT_EQ(fields.rd, 1);
  EXPECT_EQ(fields.Operation, OPERATION::SUB);
}

TEST(Decode_I_type_Test, ADDI) {

  DecodedInstruction fields {};

  fields.raw_inst = 0x02810093; // addi x1, x2, 40
  decode(fields);

  EXPECT_EQ(fields.rd, 1);
  EXPECT_EQ(fields.rs1, 2);
  EXPECT_EQ(fields.imm, 40);
  EXPECT_EQ(fields.Operation, OPERATION::ADDI);
}

TEST(Decode_I_type_Test, LB) {

  DecodedInstruction fields {};

  fields.raw_inst = 0x00028503; // lb x10, 0(x5)
  decode(fields);

  EXPECT_EQ(fields.rd, 10);
  EXPECT_EQ(fields.rs1, 5);
  EXPECT_EQ(fields.imm, 0);
  EXPECT_EQ(fields.Operation, OPERATION::LB);
}

TEST(Decode_I_type_Test, IMM_sign_ext) {
  // Check if immediate gets properly sign extended

  DecodedInstruction fields {};

  fields.raw_inst = 0xfec10093; // addi x1, x2, -20
  decode(fields);

  EXPECT_EQ(fields.imm, -20);

}

TEST(Decode_I_type_Test, IMM_sign_ext_max) {
  // Check if immediate gets properly sign extended
  
  DecodedInstruction fields {};

  fields.raw_inst = 0xfff10093; // addi x1, x2, -1
  decode(fields);

  EXPECT_EQ(fields.imm, -1);

}