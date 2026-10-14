#pragma once
#include <stdint.h>

#define op(name) Op##name,
typedef enum : uint8_t {
#include "opcode.def"
} OpCode;

static const OpCode OPCODES_WITH_ARGS[] = {
#include "opcodes_with_args.def"
};
#undef op

void
opcode_disassemble (OpCode code, char *buf);

int
opcode_has_args (OpCode code);
