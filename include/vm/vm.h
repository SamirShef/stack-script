#pragma once
#include "vm/call_frame.h"
#include "vm/chunk.h"
#include "vm/value.h"

#include <stddef.h>
#include <string.h>

#define STACK_SIZE 256
#define CALL_STACK_SIZE 64

typedef struct {
    Chunk    *chunks;
    size_t    chunks_count;
    size_t    ip;
    Value     stack[STACK_SIZE];
    CallFrame call_stack[CALL_STACK_SIZE];
    size_t    frame_idx;
} VM;

VM
vm_create ();

size_t
vm_add_chunk (VM *vm, Chunk chunk);
