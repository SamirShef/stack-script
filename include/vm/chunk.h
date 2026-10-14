#pragma once
#include "vm/value.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *bytecode;
    size_t   count;
    size_t   capacity;
    Value   *constants;
    size_t   constants_count;
} Chunk;
