#include "registers.h"
#ifndef memory_h
#define memory_h

/* prefixy */
#define segment_override_value 0x26
#define operand_override_value 0x66
#define address_override_value 0x67

/* instrukce */
#define add_R8_to_RM8 0x00
#define add 0x03
#define xor 0x33
#define increment_EDX 0x42
#define increment_EBX 0x43
#define decrement_ECX 0x49
#define jump_not_equal 0x75
#define jump_not_parity 0x7B
#define compare 0x83
#define move_to_R8 0x8A
#define move_from_segment 0x8C
#define move_to_segment 0x8E
#define move_AH 0xB4
#define move_AX 0xB8
#define move_DX 0xBA
#define move_BX 0xBB
#define move_SI 0xBE
#define move_DI 0xBF
#define move_IMM16_to_RM16 0xC7
#define interrupt 0xCD
#define jump 0xEB
#define increment 0xFF

#define opcode_count 0x100

#define LOGGER 0
#define display_pointer /*0xA000*/ 0xB800
#define code_offset 0x100

int exec_add_R8_to_RM8(byte *memory, regs_and_flags *reg);
int exec_add(byte *memory, regs_and_flags *reg);
int exec_xor(byte *memory, regs_and_flags *reg);
int exec_increment_EDX(byte *memory, regs_and_flags *reg);
int exec_increment_EBX(byte *memory, regs_and_flags *reg);
int exec_decrement_ECX(byte *memory, regs_and_flags *reg);
int exec_jump_not_equal(byte *memory, regs_and_flags *reg);
int exec_jump_not_parity(byte *memory, regs_and_flags *reg);
int exec_compare(byte *memory, regs_and_flags *reg);
int exec_move_to_R8(byte *memory, regs_and_flags *reg);
int exec_move_from_segment(byte *memory, regs_and_flags *reg);
int exec_move_to_segment(byte *memory, regs_and_flags *reg);
int exec_move_AH(byte *memory, regs_and_flags *reg);
int exec_move_AX(byte *memory, regs_and_flags *reg);
int exec_move_DX(byte *memory, regs_and_flags *reg);
int exec_move_BX(byte *memory, regs_and_flags *reg);
int exec_move_SI(byte *memory, regs_and_flags *reg);
int exec_move_DI(byte *memory, regs_and_flags *reg);
int exec_move_IMM16_to_RM16(byte *memory, regs_and_flags *reg);
int exec_interrupt(byte *memory, regs_and_flags *reg);
int exec_jump(byte *memory, regs_and_flags *reg);
int exec_increment(byte *memory, regs_and_flags *reg);



void print_memory(byte *memory, int memSize);
void print_byte(byte b);

int get_rm_field(byte addr_mode);
int get_adressing_mode(byte addr_mode);
int get_modifier(byte addr_mode);

half_register* get_register(int correct_part_of_addr_mode, regs_and_flags *reg);
half_register* get_segment(int correct_part_of_addr_mode, regs_and_flags *reg);
#endif