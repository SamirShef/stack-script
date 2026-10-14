#pragma once
#include "vm/chunk.h"

#include <stddef.h>

typedef struct {
    Chunk *chunk;
    size_t ret_addr;
} CallFrame;
