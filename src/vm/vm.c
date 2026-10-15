#include "vm/vm.h"

#include "vm/call_frame.h"
#include "vm/opcode.h"
#include "vm/value.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

VM
vm_create () {
    return (VM){ .chunks           = NULL,
                 .chunks_count     = 0,
                 .chunks_cap       = 0,
                 .ip               = 0,
                 .stack_count      = 0,
                 .call_stack_count = 0,
                 .frame_idx        = 0 };
}

size_t
vm_add_chunk (VM *vm, Chunk chunk) {
    if (vm->chunks_cap == 0) {
        vm->chunks_cap = CHUNKS_DEFAULT_CAP;
        vm->chunks     = malloc (vm->chunks_cap * sizeof (Chunk));
    } else if (vm->chunks_cap <= vm->chunks_count) {
        vm->chunks_cap *= 2;
        void *tmp = realloc (vm->chunks, vm->chunks_count * sizeof (Chunk));
        if (tmp == NULL) {
            perror ("Realloc is fail");
            exit (1);
        }
        vm->chunks = tmp;
    }
    vm->chunks[vm->chunks_count++] = chunk;
    return vm->chunks_count - 1;
}

size_t
vm_push_call_frame (VM *vm, CallFrame frame) {
    vm->call_stack[vm->call_stack_count] = frame;
    return vm->call_stack_count++;
}

void
vm_pop_call_frame (VM *vm) {
    --vm->call_stack_count;
}

size_t
vm_read_arg (VM *vm) {
    return (size_t) vm->call_stack[vm->frame_idx].chunk->bytecode[vm->ip++];
}

size_t
vm_push_stack (VM *vm, Value val) {
    vm->stack[vm->stack_count] = val;
    return vm->stack_count++;
}

Value
vm_pop_stack (VM *vm) {
    --vm->stack_count;
    return vm->stack[vm->stack_count];
}

ResultCode
vm_run (VM *vm) {
    while (1) {
        CallFrame frame = vm->call_stack[vm->frame_idx];
        Chunk    *chunk = frame.chunk;
        if (vm->ip >= chunk->count) {
            if (vm->frame_idx == 0) {
                break;
            }
            perror ("Function does not return value");
            return RcError;
        }
        switch ((OpCode) chunk->bytecode[vm->ip++]) {
        case OpAdd: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_add (a, b, &res)) {
                perror ("Cannot add two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpSub: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_sub (a, b, &res)) {
                perror ("Cannot subtract two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpMul: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_mul (a, b, &res)) {
                perror ("Cannot multiply two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpDiv: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_div (a, b, &res)) {
                perror ("Cannot divide two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpRem: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_rem (a, b, &res)) {
                perror ("Cannot remainder two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpGt: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_gt (a, b, &res)) {
                perror ("Cannot compare two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpGtEq: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_gteq (a, b, &res)) {
                perror ("Cannot compare two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpLt: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_lt (a, b, &res)) {
                perror ("Cannot compare two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpLtEq: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_lteq (a, b, &res)) {
                perror ("Cannot compare two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpEqEq: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_eqeq (a, b, &res)) {
                perror ("Cannot compare two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpNEq: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_neq (a, b, &res)) {
                perror ("Cannot compare two values");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpNot: {
            Value b = vm_pop_stack (vm);
            Value a = vm_pop_stack (vm);
            Value res;
            if (!val_not (a, &res)) {
                perror ("Cannot invert value");
                return RcError;
            }
            vm_push_stack (vm, res);
            break;
        }
        case OpDup: {
            Value top = vm->stack[vm->stack_count - 1];
            vm_push_stack (vm, top);
            break;
        }
        case OpPush: {
            size_t idx = vm_read_arg (vm);
            vm_push_stack (vm, chunk->consts[idx]);
            break;
        }
        case OpPop: {
            vm_pop_stack (vm);
            break;
        }
        case OpPrint: {
            Value val = vm_pop_stack (vm);
            switch (val.kind) {
            case VkStr: printf ("%s\n", val.data.str.data); break;
            case VkReal: printf ("%g\n", val.data.real); break;
            case VkInt: printf ("%ld\n", val.data.integer); break;
            }
            break;
        }
        case OpLoadGlobal: break;
        case OpStoreGlobal: break;
        case OpLoadLocal: break;
        case OpStoreLocal: break;
        case OpCall: break;
        case OpJumpZero: {
            Value cond = vm_pop_stack (vm);
            Value res;
            if (!val_not (cond, &res)) {
                perror ("Cannot invert value");
                return RcError;
            }
            size_t major = vm_read_arg (vm);
            size_t midle = vm_read_arg (vm);
            size_t minor = vm_read_arg (vm);
            size_t idx   = (major << 16ULL) | (midle << 8ULL) | minor;
            if (cond.data.integer == 0) {
                vm->ip = idx;
            }
            break;
        }
        case OpJump: {
            size_t major = vm_read_arg (vm);
            size_t midle = vm_read_arg (vm);
            size_t minor = vm_read_arg (vm);
            size_t idx   = (major << 16ULL) | (midle << 8ULL) | minor;
            vm->ip       = idx;
            break;
        }
        case OpRet: break;
        case OpHalt:
            // halt
            break;
        }
    }
    return RcSuccess;
}
