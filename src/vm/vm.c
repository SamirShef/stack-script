#include "vm/vm.h"

#include <stdio.h>
#include <stdlib.h>

VM
vm_create () {
    return (VM){ .chunks = NULL, .chunks_count = 0, .ip = 0, .frame_idx = 0 };
}

size_t
vm_add_chunk (VM *vm, Chunk chunk) {
    if (vm->chunks_count == 0) {
        vm->chunks = malloc (sizeof (Chunk));
    } else {
        void *tmp = realloc (vm->chunks, (vm->chunks_count + 1) * sizeof (Chunk));
        if (tmp == NULL) {
            perror ("Realloc is fail");
            exit (1);
        }
        vm->chunks = tmp;
    }
    vm->chunks[vm->chunks_count++] = chunk;
    return vm->chunks_count - 1;
}
