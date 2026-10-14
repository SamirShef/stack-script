#pragma once
#include <stddef.h>
#include <stdint.h>

typedef enum : uint8_t {
#define op(name) Op##name,
#include "opcode.def"
#undef op
} OpCode;

static const struct {
    OpCode code;
    size_t count;
} OPCODES_WITH_ARGS[] = {
#define op(name, c) { .code = Op##name, .count = (c) },
#include "opcodes_with_args.def"
#undef op
};

void
opcode_disassemble (OpCode code, char *buf);

size_t
opcode_args_count (OpCode code);
