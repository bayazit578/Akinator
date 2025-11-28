#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "dump.h"

int StackInit(stack** stk, size_t in_cap, error* err_info) {
    int err_no = no_err;
    *stk = (stack*)calloc(1, sizeof(stack));

    (*stk)->capacity = in_cap;
    // printf("%d\n", (*stk)->capacity);

    (*stk)->data = (stack_type*)calloc((*stk)->capacity, sizeof(stack_type));
    (*stk)->size = MINSIZE;
    (*stk)->data[0] = (*stk)->data[(*stk)->capacity - 1] = KAMIKADZE;

    STACK_CHECK(stk, err_info, err_no);
    return no_err;
}

int StackPush(stack** stk, stack_type elem, error* err_info) {
    int err_no = no_err;
    STACK_CHECK(stk, err_info, err_no);

    if((*stk)->size + 1 >= (*stk)->capacity - 1) {
        (*stk)->data[(*stk)->capacity - 1] = 0;
        (*stk)->capacity *= 2;
        (*stk)->data = (stack_type*)realloc((*stk)->data, (*stk)->capacity * sizeof(stack_type));
        (*stk)->data[(*stk)->capacity - 1] = KAMIKADZE;
    }

    ((*stk)->data)[(*stk)->size + 1] = elem;
    (*stk)->size++;
    // printf("\n%d\n", (*stk)->size);

    STACK_CHECK(stk, err_info, err_no);
    return no_err;
}

stack_type StackPop(stack** stk, error* err_info) {
    int err_no = no_err;
    STACK_CHECK_POP(stk, err_info, err_no);

    // printf("w%d\n", (*stk)->size);
    stack_type elem = ((*stk)->data)[(*stk)->size];
    ((*stk)->data)[(*stk)->size] = 0;
    (*stk)->size--;
    // printf("\n%d\n", (*stk)->size);

    STACK_CHECK_POP(stk, err_info, err_no);
    return elem;
}

int StackDestroy(stack** stk, error* err_info) {
    int err_no = no_err;
    STACK_CHECK(stk, err_info, err_no);

    free((*stk)->data);
    (*stk)->data = NULL;
    free(*stk);
    *stk = NULL;
    return no_err;
}
