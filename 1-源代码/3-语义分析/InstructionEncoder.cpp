// InstructionEncoder.cpp
#include "InstructionEncoder.h"
#include <cstdint>

// —————————————————————————————————————————————
// 1) 控制流
// 无条件跳转 B <label>
uint32_t encodeB(int32_t offset) {
    // offset 必须是 4 字节对齐，且能 fit 26b*2
    uint32_t imm26 = (uint32_t)(offset >> 2) & 0x03ffffffu;
    // opcode: 0b000101 imm26
    return (0b000101u << 26) | imm26;
}

// 返回 RET
uint32_t encodeRET() {
    return 0xd65f03c0u;
}

// 空指令 NOP
uint32_t encodeNOP() {
    return 0xd503201fu;
}

// —————————————————————————————————————————————
// 2) 〈Data Processing – Immediate〉
uint32_t encodeADDimm(uint8_t rd, uint8_t rn, uint16_t imm) {
    // 32-bit ADD immediate: sf=0, opc=00, S=0, opcode(24‐21)=1001
    // base = 0x11000000
    uint32_t imm12 = imm & 0xfffu;            // 12-bit
    return 0x11000000u
           | (imm12 << 10)
           | (uint32_t(rn) << 5)
           | uint32_t(rd);
}

uint32_t encodeSUBimm(uint8_t rd, uint8_t rn, uint16_t imm) {
    // 32-bit SUB immediate: sf=0, opc=01, S=0, opcode=1001
    // base = 0x51000000
    uint32_t imm12 = imm & 0xfffu;
    return 0x51000000u
           | (imm12 << 10)
           | (uint32_t(rn) << 5)
           | uint32_t(rd);
}

// MOVZ (move wide immediate)
//   movz rd, #imm16, LSL #(highHalf?16:0)
uint32_t encodeMOVz(uint8_t rd, uint16_t imm16, bool highHalf) {
    // sf=0, opc=2 (MOVZ), opcode=100101, base=0x52800000
    uint32_t hw = highHalf ? 1u : 0u;
    return 0x52800000u
           | (hw << 21)                     // LSL 高半字
           | (uint32_t(imm16 & 0xffffu) << 5)
           | uint32_t(rd);
}

// CMP immediate （等价于 SUBS WZR, rn, #imm）
uint32_t encodeCMPimm(uint8_t rn, uint16_t imm) {
    // 32-bit SUBS immediate: sf=0, opc=01 (SUB), S=1, opcode=1001 ➔ base=0x71000000
    uint32_t imm12 = imm & 0xfffu;
    return 0x71000000u
           | (imm12 << 10)
           | (uint32_t(rn) << 5)
           | 31u;    // WZR 编号 31
}

// CSET rd, cond （alias for CSEL rd, WZR, WZR, cond）
uint32_t encodeCSET(uint8_t rd, uint8_t cond) {
    // 32-bit CSEL: sf=0, opcode=1010_100, base=0x1A200000
    // Rn=WZR(31), Rm=WZR(31), cond 放在 bits[15:12]
    return 0x1A200000u
           | (31u   << 5)    // Rn = WZR
           | (31u   << 16)   // Rm = WZR
           | (uint32_t(cond & 0xFu) << 12)
           | uint32_t(rd);
}

// —————————————————————————————————————————————
// 3) 〈Load/Store Unsigned Immediate〉
//
// STR Wt, [Xn, #imm]   (32-bit 存 4-byte，imm 必须 4 字节对齐)
// LDR Wt, [Xn, #imm]   (32-bit 载 4-byte，imm 必须 4 字节对齐)
// 立即数在编码中以 imm12<<2 形式出现

uint32_t encodeSTR(uint8_t rt, uint8_t rn, int16_t offset) {
    // base for STR (unsigned imm, 32-bit) = 0x39000000
    uint32_t imm12 = (uint32_t(offset) >> 2) & 0xfffu;
    return 0x39000000u
           | (imm12 << 10)
           | (uint32_t(rn) << 5)
           | uint32_t(rt);
}

uint32_t encodeLDR(uint8_t rt, uint8_t rn, int16_t offset) {
    // base for LDR (unsigned imm, 32-bit) = 0x39400000
    uint32_t imm12 = (uint32_t(offset) >> 2) & 0xfffu;
    return 0x39400000u
           | (imm12 << 10)
           | (uint32_t(rn) << 5)
           | uint32_t(rt);
}

// —————————————————————————————————————————————
// 4) 〈Load/Store Pair, Immediate〉 （64-bit 版，用来存/取一对寄存器）
//
// STP rt1, rt2, [rn, #imm]!
// LDP rt1, rt2, [rn], #imm
//
// imm 必须 8 字节对齐，编码里以 imm7<<3 的形式出现

uint32_t encodeSTP(uint8_t rt1, uint8_t rt2, uint8_t rn, int16_t offset) {
    // 存 64-bit 对，base unsigned imm = 0xA9000000
    // pre-index: P=1,U=0,W=1 ➜ P(bit24)=1, U(bit23)=0, W(bit21)=1
    uint32_t imm7 = (uint32_t(offset) >> 3) & 0x7fu;
    return 0xA9000000u
           | (imm7 << 15)
           | (1u << 24)    // P
           | (0u << 23)    // U
           | (1u << 21)    // W
           | (uint32_t(rn) << 5)
           | (uint32_t(rt2) << 10)
           | uint32_t(rt1);
}

uint32_t encodeLDP(uint8_t rt1, uint8_t rt2, uint8_t rn, int16_t offset) {
    // 取 64-bit 对，base unsigned imm = 0xA9400000
    // post-index: P=0,U=1,W=1 ➜ P=0, U=1, W=1
    uint32_t imm7 = (uint32_t(offset) >> 3) & 0x7fu;
    return 0xA9400000u
           | (imm7 << 15)
           | (0u << 24)    // P
           | (1u << 23)    // U
           | (1u << 21)    // W
           | (uint32_t(rn) << 5)
           | (uint32_t(rt2) << 10)
           | uint32_t(rt1);
}

// 5) Data-processing (register): ADD rd, rn, rm
uint32_t encodeADDreg(uint8_t rd, uint8_t rn, uint8_t rm) {
    return 0x0B000000u
           | (uint32_t(rm) << 16)
           | (uint32_t(rn) << 5)
           |  uint32_t(rd);
}

// 6) Compare register: CMP rn, rm  (＝ SUBS WZR, rn, rm)
uint32_t encodeCMPreg(uint8_t rn, uint8_t rm) {
    // 32-bit SUBS (shifted register, no shift) with WZR destination:
    //   sf=0, opc=1, S=1, opcode=10001011000 → base = 0x2B000000 | S-bit
    // Actually: SUBS register base = 0x6B000000
    //   bits[20:16] = Rm, [9:5] = Rn, [4:0] = 31 (WZR)
    return 0x6B000000u
           | (uint32_t(rm) << 16)
           | (uint32_t(rn) << 5)
           |  31u;
}

// 7) Conditional branch: B.<cond> offset
uint32_t encodeBCond(uint8_t cond, int32_t offset) {
    // imm19 = (offset >> 2) & 0x7FFFF
    // opcode = 0b01010100 (0x54) at bits[31:24]
    // 32-bit instruction = 0b01010100|imm19|cond
    uint32_t imm19 = (uint32_t(offset) >> 2) & 0x7FFFFu;
    return (0x54u << 24)
           | (imm19 << 5)
           | (cond & 0xFu);
}