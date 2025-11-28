#ifndef DUMP_STACK_H
#define DUMP_STACK_H

#include <stdlib.h>
#include "types.h"

const int MINCAP = 2;
const int MAXCAP = 1e5;
const int MINSIZE = 0;
const int MAXSIZE = 1e5;

int StackDump(stack** stk, error* err_info);
int StackVerify(stack** stk);
void PrintError(error* err_info);
void AboutError(const char* file, const char* func,
                int line, int err_no, error* err_info);

#endif // DUMP_STACK_H
