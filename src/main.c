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

    size_t first_const_idx = chunk_add_constant (&chunk, val_from_integer (5));

    chunk_add_inst (&chunk, OpPush);
    chunk_add_inst (&chunk, first_const_idx);
    chunk_add_inst (&chunk, OpDup);
    chunk_add_inst (&chunk, OpMul);
    chunk_add_inst (&chunk, OpPrint);

    vm_add_chunk (&vm, chunk);
    vm_push_call_frame (&vm, (CallFrame){ .chunk = &chunk, .ret_addr = 0 });
    if (debug) {
        chunk_disassemble (&chunk);
    }

    return vm_run (&vm);
}
