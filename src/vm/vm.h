//
//  vm.h
//
//  Created by Shady Khalifa on 08/01/18.
//  Copyright (c) 2018 Shady Khalifa. All rights reserved.
//

/*
                [VM Instructions]

- MOV           to move data into registers or the memory.
- PUT <num>     to put immediate <num> into register GA [general register].
- LC            to load a character into GA from a memory address which is stored in GA before execution.
- LI            just like LC but dealing with integer instead of character.
- SC            to store the character in GA into the memory whose address is stored on the top of the stack.
- SI            just like SC but dealing with integer instead of character.
- PUSH          push an immediate value or a register's value onto the stack.
- JMP <addr>    will unconditionally set the value PC register to <addr>.
- JZ            jump if GX is zero [used in conditional jump].
- JNZ           jump if GX is not zero [used in conditional jump].
- CALL <addr>   to call the function whose starting point is <addr>.
- RET           to fetch the bookkeeping information to resume previous execution.
- ENT <size>    is called when we are about to enter the function call to "make a new calling frame".
- ADJ <size>    is to adjust the stack, to "remove arguments from frame".
- LEV           another instruction to accomplish the work of MOV, POP and RET
- LEA           load address for arguments [used in functions call].

                [Mathmetical Instructions]
Our VM will provide an instruction for each operators in C language.
Each operator has two arguments: the first one is stored on the top of the stack
while the second is stored in GR. 
The order matters especially in operators like -, /
After the calculation is done, the argument on the stack will be poped out
and the result will be stored in GR. So you are not able to fetch the first argument
from the stack after the calculation, please note that.

*/
enum {
    // instructions
    LEA, PUT, JMP, CALL, JZ, JNZ, ENT, ADJ, LEV, LI, LC, SI, SC, PUSH,
    // Operators
    OR, XOR, AND, EQ, NE, LT, GT, LE, GE, SHL, SHR, ADD, SUB, MUL, DIV, MOD,
    // Built-in
    OPEN, READ, CLOS, PRTF, PRTLN, POW, MALC, MSET, MCMP, EXIT 
    };

int     vm_bootstrap();