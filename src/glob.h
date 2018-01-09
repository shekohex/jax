//
//  glob.h
//
//  Created by Shady Khalifa on 08/01/18.
//  Copyright (c) 2018 Shady Khalifa. All rights reserved.
//
#ifndef INPUT_SIZE
#define INPUT_SIZE 20
#endif
#ifndef GOLOB_H
#define GOLOB_H
// This file used to share vars between files

int token;                    // current token
int token_val;                // value of current token (mainly for number)
char *src_begin;
char *src, *old_src;          // pointer to source code string;
int poolsize;                 // default size of text/data/stack
int line;                     // line number
int *begin_text;
int *begin_stack;
signed char *begin_data;
int *text,                    // text segment
    *old_text,                // for dump text segment
    *stack;                   // stack
signed char *data;                   // data segment
int *pc, *bp, *sp, gr, cycle; // virtual machine registers
int *current_id,              // current parsed ID
    *symbols;                 // symbol table
int *idmain;                  // the `main` function
int basetype;                   // the type of a declaration
int expr_type;                  // the type of an expression
// function frame
//
// 0: arg 1
// 1: arg 2
// 2: arg 3
// 3: return address
// 4: old bp pointer  <- index_of_bp
// 5: local var 1
// 6: local var 2
int index_of_bp; // index of bp pointer on stack
// DEBUGING
int debug;    // print the executed instructions
unsigned int break_point;
int continue_run;
int meet_bp;

char input_str[INPUT_SIZE + 1];

#endif // GOLOB