#include "vm/call_frame.h"
#include "vm/chunk.h"
#include "vm/opcode.h"
#include "vm/value.h"
#include "vm/vm.h"

#include <stddef.h>
#include <string.h>

int debug = 0;

int
main (int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        if (strcmp ("--debug", argv[i]) == 0) {
            debug = 1;
        }
    }

    VM    vm    = vm_create ();
    Chunk chunk = chunk_create ();

    size_t first_const_idx  = chunk_add_constant (&chunk, val_from_integer (5));
    size_t second_const_idx = chunk_add_constant (&chunk, val_from_integer (2));
    size_t glob             = vm_add_global (&vm, val_from_real (0.04));

    chunk_add_inst (&chunk, OpPush);           // 0
    chunk_add_inst (&chunk, first_const_idx);  // 1
    chunk_add_inst (&chunk, OpDup);            // 2
    chunk_add_inst (&chunk, OpEqEq);           // 3
    chunk_add_inst (&chunk, OpJumpZero);       // 4
    chunk_add_inst (&chunk, 0);                // 5
    chunk_add_inst (&chunk, 0);                // 6
    chunk_add_inst (&chunk, 20);               // 7
    chunk_add_inst (&chunk, OpPush);           // 8
    chunk_add_inst (&chunk, first_const_idx);  // 9
    chunk_add_inst (&chunk, OpDup);            // 10
    chunk_add_inst (&chunk, OpMul);            // 11
    chunk_add_inst (&chunk, OpLoadGlobal);     // 12
    chunk_add_inst (&chunk, 0);                // 13
    chunk_add_inst (&chunk, OpMul);            // 14
    chunk_add_inst (&chunk, OpPrint);          // 15
    chunk_add_inst (&chunk, OpJump);           // 16
    chunk_add_inst (&chunk, 0);                // 17
    chunk_add_inst (&chunk, 0);                // 18
    chunk_add_inst (&chunk, 26);               // 19
    chunk_add_inst (&chunk, OpPush);           // 20
    chunk_add_inst (&chunk, second_const_idx); // 21
    chunk_add_inst (&chunk, OpPush);           // 22
    chunk_add_inst (&chunk, first_const_idx);  // 23
    chunk_add_inst (&chunk, OpRem);            // 24
    chunk_add_inst (&chunk, OpPrint);          // 25
    chunk_add_inst (&chunk, OpHalt);           // 26

    vm_add_chunk (&vm, chunk);
    vm_push_call_frame (&vm, (CallFrame){ .chunk = &chunk, .ret_addr = 0 });
    if (debug) {
        chunk_disassemble (&chunk);
    }

    return vm_run (&vm);
}
