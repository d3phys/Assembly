#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

#include <stdint.h>

const size_t VRAM_ADDR = 64;
const size_t RAM_CAP   = 128;
const size_t N_REGS     = 0x08;

const unsigned int SIGNATURE  = 'ASS';
const unsigned int VERSION    = 0;
const unsigned int PATCHLEVEL = 6;

struct header_t {
        unsigned int signature  = SIGNATURE;
        unsigned int version    = VERSION;
        unsigned int patchlevel = PATCHLEVEL;
};

const unsigned int SEED = 0xDED64;

typedef double arg_t;
typedef uint16_t cmd_t;
typedef uint8_t  opcode_t;

const uint16_t MSB = ~((cmd_t)(~0x00) >> 0x01);

const cmd_t VAL_T = MSB >> 0x00;
const cmd_t MEM_T = MSB >> 0x01;
const cmd_t REG_T = MSB >> 0x02;

#define CMD(name, opcode, mnemonic, hash)    \
        const opcode_t name      = opcode;        \
        const char MN_##name[]   = mnemonic; \
        const uint32_t HASH_##name   = hash; \

#include <commands>

#undef CMD

#define REG(name, num, mnemonic, hash)     \
        const arg_t name = num;            \
        const char MN_##name[] = mnemonic; \

#include <registers>

#undef REG 


#endif /* ASSEMBLY_H_ */
