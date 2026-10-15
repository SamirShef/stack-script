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
        variant (OpLoadGlobal);
        variant (OpStoreGlobal);
        variant (OpLoadLocal);
        variant (OpStoreLocal);
        variant (OpCall);
        variant (OpJumpZero);
        variant (OpJump);
        variant (OpRet);
        variant (OpHalt);
#undef variant
    }
}

size_t
opcode_args_count (OpCode code) {
    for (size_t i = 0; i < sizeof (OPCODES_WITH_ARGS) / sizeof (OPCODES_WITH_ARGS[0]);
         ++i) {
        if (OPCODES_WITH_ARGS[i].code == code) {
            return OPCODES_WITH_ARGS[i].count;
        }
    }
    return 0;
}
