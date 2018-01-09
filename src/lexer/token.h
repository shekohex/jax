//
//  token.h
//
//  Created by Shady Khalifa on 08/01/18.
//  Copyright (c) 2018 Shady Khalifa. All rights reserved.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <stdint.h>

//	================
//	PREFIX OPERATORS
//	================
//	+		Unary PLUS
//	-		Unary MINUS
//	!		Logical NOT
//	~		Bitwise NOT

//	================
//	INFIX OPERATORS
//	================
//	<<		Bitwise left shift (160)
//	>>		Bitwise right shift (160)
//	*		Multiply (150) (associativity left)
//	/		Divide (150) (associativity left)
//	%		Remainder (150) (associativity left)
//	&		Bitwise AND (150) (associativity left)
//	+		Add (140) (associativity left)
//	-		Subtract (140) (associativity left)
//	|		Bitwise OR (140) (associativity left)
//	^		Bitwise XOR (140) (associativity left)
//	<		Less than (130)
//	<=		Less than or equal (130)
//	>		Greater than (130)
//	>=		Greater than or equal (130)
//	==		Equal (130)
//	!=		Not equal (130)
//	===		Identical (130)
//	!==		Not identical (130)
//	~=		Pattern match (130)
//	&&		Logical AND (120) (associativity left)
//	||		Logical OR (110) (associativity left)
//	?:		Ternary conditional (100) (associativity right)
//	=		Assign (90) (associativity right)
//	*=		Multiply and assign (90) (associativity right)
//	/=		Divide and assign (90) (associativity right)
//	%=		Remainder and assign (90) (associativity right)
//	+=		Add and assign (90) (associativity right)
//	-=		Subtract and assign (90) (associativity right)
//	&=		Bitwise AND and assign (90) (associativity right)
//	^=		Bitwise XOR and assign (90) (associativity right)
//	|=		Bitwise OR and assign (90) (associativity right)

enum {
  Num = 100, Fun, Sys, Glo, Loc, Id,
  Char, Else, Enum, If, Int, Return, Sizeof, While,
  True, False, GolVar, LocVar,
  Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};

// fields of identifier
enum { Token, Hash, Name, Type, Class, Value, BType, BClass, BValue, IdSize };

// types of variable/function
enum { CHAR, INT, PTR };

// type of declaration.
enum { Global, Local };
const char		    *token_name (int token);

#endif