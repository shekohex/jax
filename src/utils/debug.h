//
//  debug.h
//
//  Created by Shady Khalifa on 08/01/18.
//  Copyright (c) 2018 Shady Khalifa. All rights reserved.
//

#ifndef SUPPORT_DEBUG
// Uncommint this to enable debugger
// sometimes Debugger is so buggy :)
// #define SUPPORT_DEBUG 

void  debug_asm(int op);
int print_spec_text(int *cur_text);
void print_text();
void print_data();
void print_symbol_table();
void print_source_code();
void debug_usage();
int meet_break_point(int *pc);
int inst_has_argu(int inst);

const char* inst_2_str(int inst);
const char *class_str(int cls);
const char * type_str(int type);
void show_regs();
int is_data(unsigned int addr);
int is_text(unsigned int addr);
int is_stack(unsigned int addr);
int run_debug_func(char *cmd_line);
int meet_break_point(int *pc);
void print_symbol_table();
// return 1: has argument
// return 0: has no argument
int print_spec_text(int *cur_text);
void print_source_code();
void print_text();
void print_data();
void debug_usage();
#endif // SUPPORT_DEBUG