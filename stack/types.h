#ifndef STRUCT_H
#define STRUCT_H

#include <stdlib.h>
#include <stdint.h>

enum ErrNo {
        no_err             = 0,
        err_stack_ptr      = 2,
        err_data_ptr       = 4,
        err_stack_capacity = 8,
        err_stack_size     = 16,
        err_poison_element = 32,
        err_canary         = 64,
        err_spu            = 128,
        err_spu_ptr        = 512,
        err_comm_buff_ptr  = 1024,
        err_registers_ptr  = 2048,
        err_pointer        = 4096,
        };

typedef char* stack_type;

typedef struct stack {
        stack_type* data;
        size_t      size;
        size_t      capacity;
        size_t      instruction_pointer;
        } stack;

typedef struct proc {
        stack*   stk;
        stack*   stk_funcs;
        int16_t* command_buff;
        int*     registers;
        int*     RAM;
        size_t   buff_size;
        size_t   instruction_pointer;
        } proc;

typedef struct error {
        char* err_file;
        char* err_func;
        int   err_line;
        int   err_no;
        } error;

#endif // STRUCT_H
