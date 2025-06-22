// InstructionEncoder.h
#ifndef INSTRUCTION_ENCODER_H
#define INSTRUCTION_ENCODER_H

#include <cstdint>

// 无条件跳转 B <label>
uint32_t encodeB(int32_t offset);

// 返回 RET
uint32_t encodeRET();

// 空指令 NOP
uint32_t encodeNOP();

// ADD (immediate): add rd, rn, #imm
uint32_t encodeADDimm(uint8_t rd, uint8_t rn, uint16_t imm);

// SUB (immediate): sub rd, rn, #imm
uint32_t encodeSUBimm(uint8_t rd, uint8_t rn, uint16_t imm);

// MOVZ (move wide immediate): movz rd, #imm16, {LSL #16 if highHalf}
uint32_t encodeMOVz(uint8_t rd, uint16_t imm16, bool highHalf);

// CMP immediate: cmp rn, #imm  (encoded as subs wzr, rn, #imm)
uint32_t encodeCMPimm(uint8_t rn, uint16_t imm);

// CSET (condition set): cset rd, <cond>
//   cond: 0=eq,1=ne,2=hs,3=lo,4=mi,5=pl,6=vs,7=vc,8=hi,9=ls,10=ge,11=lt,12=gt,13=le,14=al,15=nv
uint32_t encodeCSET(uint8_t rd, uint8_t cond);

// STP (pre-index): stp rt1, rt2, [rn, #offset]!
uint32_t encodeSTP(uint8_t rt1, uint8_t rt2, uint8_t rn, int16_t offset);

// LDP (post-index): ldp rt1, rt2, [rn], #offset
uint32_t encodeLDP(uint8_t rt1, uint8_t rt2, uint8_t rn, int16_t offset);

// STR (unsigned immediate): str rt, [rn, #offset]
uint32_t encodeSTR(uint8_t rt, uint8_t rn, int16_t offset);

// LDR (unsigned immediate): ldr rt, [rn, #offset]
uint32_t encodeLDR(uint8_t rt, uint8_t rn, int16_t offset);

// ADD sp, sp, #imm
inline uint32_t encodeADDsp(uint16_t imm) {
    return encodeADDimm(/*rd=*/31, /*rn=*/31, imm);
}

// SUB sp, sp, #imm
inline uint32_t encodeSUBsp(uint16_t imm) {
    return encodeSUBimm(/*rd=*/31, /*rn=*/31, imm);
}


// ADD (register): add rd, rn, rm
uint32_t encodeADDreg(uint8_t rd, uint8_t rn, uint8_t rm);
// Compare (register): subs wzr, rn, rm
uint32_t encodeCMPreg(uint8_t rn, uint8_t rm);
// Conditional branch B.<cond> imm
uint32_t encodeBCond(uint8_t cond, int32_t offset);
#endif // INSTRUCTION_ENCODER_H
