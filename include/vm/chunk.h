#pragma once
#include "vm/value.h"

#include <stddef.h>
#include <stdint.h>

#define BYTECODE_DEFAULT_CAP 16
#define CONSTS_DEFAULT_CAP 8

typedef struct {
    uint8_t *bytecode;
    size_t   count;
    size_t   cap;
    Value   *consts;
    size_t   consts_count;
    size_t   consts_cap;
} Chunk;

Chunk
chunk_create ();

size_t
chunk_add_inst (Chunk *chunk, uint8_t code);

size_t
chunk_add_constant (Chunk *chunk, Value constant);

void
chunk_disassemble (Chunk *chunk);
