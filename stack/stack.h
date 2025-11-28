#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "dump.h"
#include "types.h"
#include "../colors.h"

const int KAMIKADZE = 0xDEFACED;
const int POISON = 0xBADBABE;
typedef char* stack_type;

#define STACK_CHECK(stk, err_info, err_no) {                     \
    err_no = StackVerify(stk);                                    \
    if(err_no != no_err) {                                         \
        AboutError(__FILE__, __func__, __LINE__, err_no, err_info); \
        PrintError(err_info);                                        \
        StackDump(stk, err_info);                                     \
        return err_no;                                                 \
    }                                                                   \
}

#define STACK_CHECK_POP(stk, err_info, err_no) {                 \
    err_no = StackVerify(stk);                                    \
    if(err_no != no_err) {                                         \
        AboutError(__FILE__, __func__, __LINE__, err_no, err_info); \
        PrintError(err_info);                                        \
        return POISON;                                                \
    }                                                                  \
}

#define STACK_CHECK_GENERAL(err_info, err_spu_info)                       \
        if(err_info.err_no != no_err || err_spu_info.err_no != no_err) { \
            fprintf(stderr, RED "Execution terminated.\n"                   \
                                "Errno: %d\n" RESET, err_info.err_no);       \
        }                                                                     \
    return 1;

int StackInit(stack** stk, size_t size, error* err_info);
int StackPush(stack** stk, stack_type elem, error* err_info);
stack_type StackPop(stack** stk, error* err_info);
int StackDestroy(stack** stk, error* err_info);

#endif // STACK_H
