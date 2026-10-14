#include "vm/chunk.h"

#include "vm/value.h"

#include <stdio.h>
#include <stdlib.h>

Chunk
chunk_create () {
    return (Chunk){ .bytecode     = NULL,
                    .count        = 0,
                    .cap          = 0,
                    .consts       = NULL,
                    .consts_count = 0,
                    .consts_cap   = 0 };
}

size_t
chunk_add_inst (Chunk *chunk, uint8_t code) {
    if (chunk->cap == 0) {
        chunk->cap      = BYTECODE_DEFAULT_CAP;
        chunk->bytecode = malloc (chunk->cap * sizeof (uint8_t));
    } else if (chunk->cap <= chunk->count) {
        chunk->cap *= 2;
        void *tmp = realloc (chunk->bytecode, chunk->count * sizeof (uint8_t));
        if (tmp == NULL) {
            perror ("Realloc is fail");
            exit (1);
        }
        chunk->bytecode = tmp;
    }
    chunk->bytecode[chunk->count++] = code;
    return chunk->count - 1;
}

size_t
chunk_add_constant (Chunk *chunk, Value constant) {
    if (chunk->consts_cap == 0) {
        chunk->consts_cap = CONSTS_DEFAULT_CAP;
        chunk->consts     = malloc (chunk->consts_cap * sizeof (Value));
    } else if (chunk->consts_cap <= chunk->consts_count) {
        chunk->consts_cap *= 2;
        void *tmp = realloc (chunk->consts, chunk->consts_count * sizeof (Value));
        if (tmp == NULL) {
            perror ("Realloc is fail");
            exit (1);
        }
        chunk->consts = tmp;
    }
    chunk->consts[chunk->consts_count++] = constant;
    return chunk->consts_count - 1;
}
