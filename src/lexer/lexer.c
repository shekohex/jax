#include <stdbool.h>
#include <memory.h>
#include "lexer.h"
#include "token.h"
#include "../glob.h"
#define NEXT        src ++;

bool is_identifier(int token) {
    return ((token >= 'a' && token <= 'z') ||
            (token >= 'A' && token <= 'Z') ||
            (token == '_'));
}

bool is_macro(int token) {
    return (token == '#');
}
void lexer_work() {
    char *last_pos;
    int hash;

    while (token = *src) {
        ++src;

        if (token == '\n') {
            ++line;
        }
        else if (is_macro(token)) {
            // skip macro, because we will not support it
            while (*src != 0 && *src != '\n') {
                NEXT;
            }
        }
        else if (is_identifier(token)) {

            // parse identifier
            last_pos = src - 1;
            hash = token;

            while ((*src >= 'a' && *src <= 'z')  ||
                    (*src >= 'A' && *src <= 'Z') ||
                    (*src >= '0' && *src <= '9') ||
                    (*src == '_'))
            {
                hash = hash * 147 + *src; // make a random hash of the identifier
                NEXT;
            }

            // look for existing identifier, linear search
            // TODO
            current_id = symbols;
            while (current_id[Token]) {
                if (current_id[Hash] == hash &&
                    !memcmp((char *)current_id[Name], last_pos, src - last_pos)) {
                    //found one, return
                    token = current_id[Token];
                    return;
                }
                current_id = current_id + IdSize;
            }


            // store new ID
            current_id[Name] = (int)last_pos;
            current_id[Hash] = hash;
            token = current_id[Token] = Id;
            return;
        }
        else if (token >= '0' && token <= '9') {
            // parse number, three kinds: dec(123) hex(0x123) oct(017)
            token_val = token - '0';
            if (token_val > 0) {
                // dec, starts with [1-9]
                while (*src >= '0' && *src <= '9') {
                    token_val = token_val*10 + *src++ - '0';
                }
            } else {
                // starts with number 0
                if (*src == 'x' || *src == 'X') {
                    //hex
                    token = *++src;
                    // a trick !
                    while ((token >= '0' && token <= '9') ||
                            (token >= 'a' && token <= 'f') ||
                            (token >= 'A' && token <= 'F')) {
                        token_val = token_val * 16 + (token & 15) + (token >= 'A' ? 9 : 0);
                        token = *++src;
                    }
                } else {
                    // oct
                    while (*src >= '0' && *src <= '7') {
                        token_val = token_val*8 + *src++ - '0';
                    }
                }
            }

            token = Num;
            return;
        }
        else if (token == '/') {
            if (*src == '/') {
                // skip comments
                while (*src != 0 && *src != '\n') {
                    ++src;
                }
            } else {
                // divide operator
                token = Div;
                return;
            }
        }
        else if (token == '"' || token == '\'') {
            // parse string literal, currently, the only supported escape
            // character is '\n', store the string literal into data.
            last_pos = data;
            while (*src != 0 && *src != token) {
                token_val = *src++;
                if (token_val == '\\') {
                    // escape character
                    token_val = *src++;
                    if (token_val == 'n') {
                        token_val = '\n';
                    }
                }

                if (token == '"') {
                    *data++ = token_val;
                }
            }

            src++;
            // if it is a single character, return Num token
            if (token == '"') {
                token_val = (int)last_pos;
            } else {
                token = Num;
            }

            return;
        }
        else if (token == ':') {
            // Var assin
            if (*src == '=') {
                NEXT;
                token = GolVar;
                printf("%s\n", "meet !");
            }
            printf("%s\n", "not meet !");
            return;
        }
        else if (token == '=') {
            // parse '==' and '='
            if (*src == '=') {
                NEXT;
                token = Eq;
            } else {
                token = Assign;
            }
            return;
        }
        else if (token == '+') {
            // parse '+' and '++'
            if (*src == '+') {
                NEXT;
                token = Inc;
            } else {
                token = Add;
            }
            return;
        }
        else if (token == '-') {
            // parse '-' and '--'
            if (*src == '-') {
                NEXT;
                token = Dec;
            } else {
                token = Sub;
            }
            return;
        }
        else if (token == '!') {
            // parse '!='
            if (*src == '=') {
                NEXT;
                token = Ne;
            }
            return;
        }
        else if (token == '<') {
            // parse '<=', '<<' or '<'
            if (*src == '=') {
                NEXT;
                token = Le;
            } else if (*src == '<') {
                NEXT;
                token = Shl;
            } else {
                token = Lt;
            }
            return;
        }
        else if (token == '>') {
            // parse '>=', '>>' or '>'
            if (*src == '=') {
                NEXT;
                token = Ge;
            } else if (*src == '>') {
                NEXT;
                token = Shr;
            } else {
                token = Gt;
            }
            return;
        }
        else if (token == '|') {
            // parse '|' or '||'
            if (*src == '|') {
                NEXT;
                token = Lor;
            } else {
                token = Or;
            }
            return;
        }
        else if (token == '&') {
            // parse '&' and '&&'
            if (*src == '&') {
                NEXT;
                token = Lan;
            } else {
                token = And;
            }
            return;
        }
        else if (token == '^') {
            token = Xor;
            return;
        }
        else if (token == '%') {
            token = Mod;
            return;
        }
        else if (token == '*') {
            token = Mul;
            return;
        }
        else if (token == '[') {
            token = Brak;
            return;
        }
        else if (token == '?') {
            token = Cond;
            return;
        }
        else if (token == '~' ||
                token == ';'  ||
                token == '{'  ||
                token == '}'  ||
                token == '('  ||
                token == ')'  ||
                token == ']'  ||
                token == ',') {
            // directly return the character as token;
            return;
        }
    }
}
