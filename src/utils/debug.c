#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../vm/vm.h"
#include "../lexer/token.h"
#include "../glob.h"


const char *inst_str[] = 
{ 
  "LEA",
  "PUT",
  "JMP",
  "CALL",
  "JZ ",
  "JNZ",
  "ENT",
  "ADJ",
  "LEV",
  "LI ",
  "LC ",
  "SI ",
  "SC ",
  "PUSH",
  " OR ",
  "XOR",
  "AND",
  "EQ ",
  "NE ",
  "LT ",
  "GT ",
  "LE ",
  "GE ",
  "SHL",
  "SHR",
  "ADD",
  "SUB",
  "MUL",
  "DIV",
  "MOD",
  " OPEN",
  "READ",
  "CLOS",
  "PRTF",
  "PRTLN ",
  "POW ",
  "MALC",
  "MSET",
  "MCMP",
  "EXIT"
};
const char *class_str_array[] = 
{
  "Num",
  "Fun",
  "Sys",
  "Glo",
  "Loc",
  "Id",
  "Char",
  "Else",
  "Enum",
  "If",
  "Int",
  "Return",
  "Sizeof",
  "While",
  "Assign",
  "Cond",
  "Lor",
  "Lan",
  "Or",
  "Xor",
  "And",
  "Eq",
  "Ne",
  "Lt",
  "Gt",
  "Le",
  "Ge",
  "Shl",
  "Shr",
  "Add",
  "Sub",
  "Mul",
  "Div",
  "Mod",
  "Inc",
  "Dec",
  "Brak"
};
const char *type_str_array[] = { "CHAR", "INT", "PTR" };
#define MAX_BREAK_POINT 10
#define INST_LEN (sizeof(inst_str)/sizeof(char*))
unsigned int break_points[MAX_BREAK_POINT];
int last_bp;
int inst_has_argu(int inst) {
  if ( (LEA <= inst) && (inst <= ADJ))
    return 1;
  else
    return 0;
}

const char* inst_2_str(int inst) {
  if ( (0 <= inst) && (inst < INST_LEN))
  {
    return inst_str[inst];
  }
  else
    return 0;
}

const char *class_str(int cls) {
  int class_index = cls-Num;

  if (0 <= class_index && class_index <= Brak)
    return class_str_array[class_index];
  else
    return "no such class";
}

const char * type_str(int type)
{
  if (0 <= type && type <= PTR)
    return type_str_array[type];
  else
    return "no such type";
}

void show_regs() {
  printf("gr: %#x(%d)\n", gr, gr);
  printf("sp: %p\n", sp);
  printf("bp: %p\n", bp);
  printf("pc: %p\n", pc);
}

int is_data(unsigned int addr) {
  if (((unsigned int)begin_data <= addr) && (addr < (unsigned int)data))
    return 1;
  else
    return 0;
}

int is_text(unsigned int addr) {
  if (((unsigned int)begin_text <= addr) && (addr < (unsigned int)text))
    return 1;
  else
    return 0;
}

int is_stack(unsigned int addr) {
  if (((unsigned int)begin_stack <= addr) && (addr < (unsigned int)begin_stack + poolsize))
    return 1;
  else
    return 0;
}

int run_debug_func(char *cmd_line) {
  switch (cmd_line[0])
  {
    case 'q':
    {
      exit(1);
    }
    case 'd':
    {
      print_data();
      break;
    }
    case 't':
    {
      print_symbol_table();
      break;
    }
    case 'h':
    case '?':
    {
      debug_usage();
      break;
    }
    case 'l':
    {
      print_source_code();
      break;
    }
    case 'e':
    {
      print_text();
      break;
    }
    case 'b': // break pointer, ex: b 0xf756301c
    {
      unsigned int addr;
      char cmd;

      sscanf(cmd_line, "%c %x\n", &cmd, &addr);
      if (last_bp < MAX_BREAK_POINT)
      {
        break_points[last_bp] = addr;
        printf("set break_points[%d]: %x\n", last_bp, addr);
        ++last_bp;
      }
      else
      {
        printf("exceed %d break points\n", MAX_BREAK_POINT);
      }
      break;
    }
    case 'x': // show data segment content, ex: x 0xf756301c
    {
      char cmd_str[5];

      switch (cmd_line[1])
      {
        case 's':
        {
          break;
        }
        case 'c':
        {
          break;
        }
        case 'i':
        {
          break;
        }
        case 'x':
        {
          break;
        }
        default:
        {
          printf("xxx\n");
          return -1;
        }

      }
      unsigned int addr;

      sscanf(cmd_line, "%s %x\n", cmd_str, &addr);
      printf("cmd: %s, addr: %#x\n", cmd_str, addr);
      #if 1
        is_text(addr);
        is_stack(addr);
        //if (((unsigned int)begin_data <= addr) && (addr < (unsigned int)data))
        if (is_data(addr) )
        {
            if (cmd_line[1] == 's')
            printf("data seg: %s\n", (char *)addr);
            if (cmd_line[1] == 'i')
            printf("data seg: %#d\n", *(int *)addr);
            if (cmd_line[1] == 'x')
            printf("data seg: %#x\n", *(int *)addr);
        }
        else if (is_text(addr) )
                printf("text seg: %#x(%d)\n", *((int *)addr), *((int *)addr));
            else if (is_stack(addr) )
                    printf("stack area: %#x(%d)\n", *((int *)addr), *((int *)addr));
                    else
                    {
                    printf("%x is not in \ntext segment (%p ~ %p)\ndata segment (%p ~ %p)\nstack range (%p ~ %p)\n", addr, begin_text, text, begin_data, data, begin_stack, begin_stack + poolsize);

                    }

        //printf("%#x(%d)\n", *((int *)addr));
      #endif
      break;
    }
    case 'r': // show registers
    {
      show_regs(); 
      break;
    }
    default:
    {
      break;
    }

  } // end switch (input_str[0])
  return 0;
}

void debug_usage() {
  printf("command\n");
  printf("s: step\n");
  printf("q: quit\n");
  printf("c: continue\n");
  printf("r: print all register content\n");
  printf("d: print data\n");
  printf("e: print text\n");
  printf("l: print source code\n");
  printf("t: print symbol table\n");
  printf("xs address: print text/data segment stack area content as string\n");
  printf("xc address: not yet complete. print text/data segment stack area content as char\n");
  printf("xi address: print text/data segment stack area content as int\n");
  printf("xx address: print text/data segment stack area content as hex\n");
  printf("b address: set breakpoint, max breakpoint is %d\n", MAX_BREAK_POINT);
}

int meet_break_point(int *pc) {
  int i;
  unsigned int cur_addr = (unsigned int)pc;
  //printf("cur_addr: %x\n", cur_addr);

  for (i = 0 ; i < last_bp ; ++i)
  {
    //printf("cur break_points[%d]: %x\n", i, break_points[i]);
    if (cur_addr == break_points[i])
    {
      printf("break_points[%d]: %x\n", i, break_points[i]);
      return 1;
    }
  }
  return 0;
}
void print_symbol_table() {
  int *cur_id;
  cur_id = symbols;

  printf("symbol table:\n");

  while(cur_id[Token])
  {
    printf("cur_id[Name]: %s\n", cur_id[Name]);
    printf("cur_id[Hash]: %#x\n", cur_id[Hash]);
    printf("cur_id[Type]: %s (%d)\n", type_str(cur_id[Type]), cur_id[Type]);
    printf("cur_id[Class]: %s (%d)\n", class_str(cur_id[Class]), cur_id[Class]);
    printf("cur_id[Value]: %#x (%d)\n", cur_id[Value], cur_id[Value]);
    cur_id = cur_id + IdSize;
  }
}

// return 1: has argument
// return 0: has no argument
int print_spec_text(int *cur_text) {
  int has_argu=0;

  const char* inst_str = inst_2_str(*cur_text);
  has_argu = inst_has_argu(*cur_text);

  if (inst_str) {
    printf("addr %p ## %s", cur_text, inst_str);
  }
  else {
    printf("addr %p ## %x", cur_text, *cur_text);
  }
  if (has_argu)
  {
    ++cur_text;
    printf(" %#x(%d)", *cur_text, *cur_text);
  }
  printf("\n");
  return has_argu;
}

void print_source_code() {
  printf("%s\n", src_begin);
}

void print_text() {
  printf("text segment:\n");

  int *cur_text = begin_text + 1;
  int i;
  int has_argu = 0;
  while (cur_text != text)
  {
    has_argu = print_spec_text(cur_text);
    if (has_argu)
      cur_text += 2;
    else
      ++cur_text;
  }

}

void print_data() {
  signed char *cur_data = begin_data;
  int print_addr = 1;

  printf("data segment:\n");

  while(cur_data != data)
  {
    if (*cur_data != 0)
    {
      if (print_addr)
      {
        printf("%p: ", cur_data);
        print_addr = 0;
      }
      printf("%c", *cur_data);
    }
    else
    {
      printf("\n");
      print_addr = 1;
    }
    ++cur_data;
  }
}