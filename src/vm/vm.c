#include "vm/vm.h"

#include <stdio.h>
#include <stdlib.h>

VM
vm_create () {
    return (VM){ .chunks       = NULL,
                 .chunks_count = 0,
                 .chunks_cap   = 0,
                 .ip           = 0,
                 .frame_idx    = 0 };
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
