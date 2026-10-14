#include "vm/chunk.h"
#include "vm/opcode.h"
#include "vm/value.h"
#include "vm/vm.h"

#include <stddef.h>

int
main (int argc, char *argv[]) {
    VM    vm    = vm_create ();
    Chunk chunk = chunk_create ();

    size_t first_const_idx  = chunk_add_constant (&chunk, val_from_integer (2));
    size_t second_const_idx = chunk_add_constant (&chunk, val_from_integer (3));

    chunk_add_inst (&chunk, OpPush);
    chunk_add_inst (&chunk, first_const_idx);
    chunk_add_inst (&chunk, OpPush);
    chunk_add_inst (&chunk, second_const_idx);
    chunk_add_inst (&chunk, OpAdd);
    chunk_add_inst (&chunk, OpPrint);

    vm_add_chunk (&vm, chunk);
    return 0;
}
