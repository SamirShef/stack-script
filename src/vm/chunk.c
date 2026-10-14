#include "vm/chunk.h"

#include "vm/opcode.h"
#include "vm/value.h"

#include <math.h>
#include <stddef.h>
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

void
chunk_disassemble (Chunk *chunk) {
    size_t count_len = (size_t) log10 ((double) chunk->count) + 1;
    for (size_t i = 0; i < chunk->count; ++i) {
        size_t i_len = (size_t) log10 (i != 0 ? (double) i : 1) + 1;
        char   buf[128];
        char   opcode_buf[16];
        OpCode opcode = (OpCode) chunk->bytecode[i];
        opcode_disassemble (opcode, opcode_buf);

        for (size_t j = 0; j < count_len - i_len; ++j) {
            buf[j] = '0';
        }

        size_t args_count = opcode_args_count (opcode);
        if (args_count == 0) {
            sprintf (buf + (count_len - i_len), "%zu: %s", i, opcode_buf);
        } else {
            ++i; // skip
            size_t arg = 0;
            for (size_t j = 0; j < args_count; ++j, ++i) {
                arg |= (size_t) chunk->bytecode[i] << ((args_count - j - 1ULL) * 8ULL);
            }
            sprintf (
                buf + (count_len - i_len),
                "%zu: %s (%zu)",
                i - args_count,
                opcode_buf,
                arg);
        }
        printf ("%s\n", buf);
    }
}
