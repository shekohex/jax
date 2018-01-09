#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "../glob.h"
#include "../utils/debug.h"
#include "vm.h"

int vm_bootstrap() {
    int op, *tmp;
    break_point = 0;
    continue_run = 0;
    meet_bp = 0;
    cycle = 0;
    while (1) {
        #ifdef SUPPORT_DEBUG
            print_spec_text(pc);
            //if (break_point == (unsigned int)pc || continue_run == 0)

            debug_input:
            while(continue_run == 0) {
            printf("%d ## debug> ", line++);
            fgets(input_str, INPUT_SIZE, stdin);

            if (input_str[0] == 's' || input_str[0] == '\n')
            {
                continue_run = 0;
                break;
            }

            if (input_str[0] == 'c')
            {
                continue_run = 1;
                break;
            }
            else
            {
                run_debug_func(input_str);
                continue_run = 0;
            }
            }

            if (meet_bp == 0 && meet_break_point(pc)) {
            meet_bp = 1;
            // printf("meet break pointer: %x\n", (unsigned int)pc);
            continue_run = 0;
            goto debug_input;
            }
            else {
            meet_bp = 0;
            }

        #endif
        cycle ++;
        op = *pc++; // get next operation code
        // VM Instructions
        if (op == PUT)       { gr = *pc++; }                                     // load immediate value to gr
        else if (op == LC)   { gr = *(char *)gr; }                               // load character to gr, address in gr
        else if (op == LI)   { gr = *(int *)gr; }                                // load integer to gr, address in gr
        else if (op == SC)   { gr = *(char *)*sp++ = gr; }                       // save character to address, value in gr, address on stack
        else if (op == SI)   { *(int *)*sp++ = gr; }                             // save integer to address, value in gr, address on stack
        else if (op == PUSH) { *--sp = gr; }                                     // push the value of gr onto the stack
        else if (op == JMP)  { pc = (int *)*pc; }                                // jump to the address
        else if (op == JZ)   { pc = gr ? pc + 1 : (int *)*pc; }                   // jump if gr is zero
        else if (op == JNZ)  { pc = gr ? (int *)*pc : pc + 1; }                   // jump if gr is zero
        else if (op == CALL) {
            *--sp = (int)(pc+1);
            pc = (int *)*pc;
        }
        //else if (op == RET)  {pc = (int *)*sp++;}                              // return from subroutine;

        else if (op == ENT)  {
            // make new stack frame
            *--sp = (int)bp;
            bp = sp;
            sp = sp - *pc++; 
        }
        else if (op == ADJ)  { sp = sp + *pc++; }                                // add esp, <size>
        else if (op == LEV)  {
            sp = bp;
            bp = (int *)*sp++;
            pc = (int *)*sp++;
        }  // restore call frame and PC
        else if (op == LEA)  { gr = (int)(bp + *pc++); }                         // load address for arguments.
       
        // Mathmetical Instructions
        else if (op == OR)  gr = *sp++ | gr;
        else if (op == XOR) gr = *sp++ ^ gr;
        else if (op == AND) gr = *sp++ & gr;
        else if (op == EQ)  gr = *sp++ == gr;
        else if (op == NE)  gr = *sp++ != gr;
        else if (op == LT)  gr = *sp++ < gr;
        else if (op == LE)  gr = *sp++ <= gr;
        else if (op == GT)  gr = *sp++ >  gr;
        else if (op == GE)  gr = *sp++ >= gr;
        else if (op == SHL) gr = *sp++ << gr;
        else if (op == SHR) gr = *sp++ >> gr;
        else if (op == ADD) gr = *sp++ + gr;
        else if (op == SUB) gr = *sp++ - gr;
        else if (op == MUL) gr = *sp++ * gr;
        else if (op == DIV) gr = *sp++ / gr;
        else if (op == MOD) gr = *sp++ % gr;
        // Built-in
        else if (op == EXIT) {
            // printf("\n exit(%d)\n", *sp);
            return *sp;
        }
        else if (op == OPEN) {
            gr = open((char *)sp[1], sp[0]);
        }
        else if (op == CLOS) { gr = close(*sp); }
        else if (op == READ) { gr = read(sp[2], (char *)sp[1], *sp); }
        else if (op == PRTF) {
            tmp = sp + pc[1];
            gr = printf((char *)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]);
        }
        else if (op == PRTLN) {
            // BUG
            tmp = sp + pc[1];
            gr = printf("%s\n", (char *)tmp[-1]);
        }
        else if (op == POW) {
            tmp = sp + pc[1];
            gr = pow(tmp[-1], tmp[-2]);
        }
        else if (op == MALC) { gr = (int)malloc(*sp); }
        else if (op == MSET) { gr = (int)memset((char *)sp[2], sp[1], *sp); }
        else if (op == MCMP) { gr = memcmp((char *)sp[2], (char *)sp[1], *sp); }
        else {
            // we hope not get here :)
            printf("unknown instruction: %d\n", op);
            return -1;
        }
    }
}
