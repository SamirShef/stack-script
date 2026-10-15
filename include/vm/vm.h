#pragma once
#include "vm/call_frame.h"
#include "vm/chunk.h"
#include "vm/value.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define STACK_SIZE 64
#define CALL_STACK_SIZE 16
#define CHUNKS_DEFAULT_CAP 8
#define GLOBALS_DEFAULT_CAP 8

typedef struct {
    Chunk    *chunks;
    size_t    chunks_count;
    size_t    chunks_cap;
    size_t    ip;
    Value     stack[STACK_SIZE];
    size_t    stack_count;
    CallFrame call_stack[CALL_STACK_SIZE];
    size_t    call_stack_count;
    size_t    frame_idx;
    Value    *globals;
    size_t    globals_cap;
    size_t    globals_count;
} VM;

typedef enum : uint8_t { RcSuccess = 0, RcError } ResultCode;

VM
vm_create ();

size_t
vm_add_chunk (VM *vm, Chunk chunk);

size_t
vm_push_call_frame (VM *vm, CallFrame frame);

void
vm_pop_call_frame (VM *vm);

size_t
vm_read_arg (VM *vm);

size_t
vm_push_stack (VM *vm, Value val);

Value
vm_pop_stack (VM *vm);

size_t
vm_add_global (VM *vm, Value val);

ResultCode
vm_run (VM *vm);
