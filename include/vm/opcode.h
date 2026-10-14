#pragma once
#include <stdint.h>

typedef enum : uint8_t {
#define op(name) Op##name,
#include "opcode.def"
#undef op
} OpCode;
