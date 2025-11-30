#include "dump_stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"
#include "types.h"
#include "../colors.h"

int StackVerify(stack** stk) {
    int err_no = no_err;

    if(*stk == NULL) {
        err_no = err_stack_ptr;
        return err_no;
    }
    if((*stk)->data == NULL)
        err_no |= err_data_ptr;
    if((*stk)->size < MINSIZE || (*stk)->size > MAXSIZE)
        err_no |= err_stack_size;
    if((*stk)->capacity < MINCAP || (*stk)->capacity > MAXCAP)
        err_no |= err_stack_capacity;
    if(((*stk)->data)[0] != KAMIKADZE || ((*stk)->data)[(*stk)->capacity - 1] != KAMIKADZE)
        err_no |= err_canary;
    return err_no;
}

int StackDump(stack** stk, error* err_info) {
    int err_no = 0;
    STACK_CHECK(stk, err_info, err_no);

    printf(YELLO "Stack size: %d\n" RESET, (*stk)->size);
    printf(YELLO "Stack capacity: %d\n" RESET, (*stk)->capacity);
    printf(YELLO "Stack contents:\n" RESET);
    for(int i = 1; i <= (*stk)->size; i++)
        printf("[%d]:%d\n", i - 1, (*stk)->data[i]);
    printf("\n" RESET);

    STACK_CHECK(stk, err_info, err_no);
    return no_err;
}

void PrintError(error* err_info) {
    fprintf(stderr, RED "In file: %s, function: %s, line: %d:\n" RESET,
            err_info->err_file, err_info->err_func, err_info->err_line);

    bool error = false;
    if(err_info->err_no & err_stack_ptr){
        fprintf(stderr, RED "Stack pointer is corrupted.\n" RESET);
        error = true;
    }
    if(err_info->err_no & err_data_ptr) {
        fprintf(stderr, RED "Data pointer is corrupted.\n" RESET);
        error = true;
    }
    if(err_info->err_no & err_stack_capacity) {
        fprintf(stderr, RED "Stack capacity has an invalid value.\n" RESET);
        error = true;
    }
    if(err_info->err_no & err_stack_size) {
        fprintf(stderr, RED "Stack size has an invalid value.\n" RESET);
        error = true;
    }
    if(err_info->err_no & err_poison_element) {
        fprintf(stderr, RED "Stack is full.\n" RESET);
        error = true;
    }
    if(err_info->err_no & err_spu) {
        fprintf(stderr, RED "Error of command execution.\n" RESET);
        error = true;
    }
    if(err_info->err_no & err_canary) {
        fprintf(stderr, RED "Canary damaged.\n" RESET);
        error = true;
    }
    if(err_info->err_no & err_spu_ptr) {
        fprintf(stderr, RED "Spu pointer is corruped.\n" RESET);
        error = true;
    }
    if(err_info->err_no & err_comm_buff_ptr) {
        fprintf(stderr, RED "Command buffer pointer is corruped.\n" RESET);
        error = true;
    }
    if(err_info->err_no & err_registers_ptr) {
        fprintf(stderr, RED "Registers pointer is corruped.\n" RESET);
        error = true;
    }
    if(err_info->err_no & err_pointer) {
        fprintf(stderr, RED "Error with instruction pointer.\n" RESET);
        error = true;
    }
    if(!error)
        fprintf(stderr, RED "Interesting unknown error.\n" RESET);
}

void AboutError(const char* file, const char* func, int line,
                int err_no, error* err_info) {
    err_info->err_file = (char*)file;
    err_info->err_func = (char*)func;
    err_info->err_line = line;
    err_info->err_no = err_no;
}
