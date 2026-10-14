#include "vm/opcode.h"

#include <stddef.h>
#include <stdio.h>

void
opcode_disassemble (OpCode code, char *buf) {
    switch (code) {
#define variant(code)                                                                    \
    case code: sprintf (buf, #code); break;
        variant (OpAdd);
        variant (OpSub);
        variant (OpMul);
        variant (OpDiv);
        variant (OpRem);
        variant (OpGt);
        variant (OpGtEq);
        variant (OpLt);
        variant (OpLtEq);
        variant (OpEqEq);
        variant (OpNEq);
        variant (OpNot);
        variant (OpDup);
        variant (OpPush);
        variant (OpPop);
        variant (OpPrint);
        variant (OpLoad);
        variant (OpStore);
        variant (OpCall);
        variant (OpJumpZero);
        variant (OpJump);
        variant (OpRet);
        variant (OpHalt);
#undef variant
    }
}

int
opcode_has_args (OpCode code) {
    for (size_t i = 0; i < sizeof (OPCODES_WITH_ARGS) / sizeof (OpCode); ++i) {
        if (OPCODES_WITH_ARGS[i] == code) {
            return 1;
        }
    }
    return 0;
}
