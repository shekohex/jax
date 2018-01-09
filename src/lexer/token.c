//
//  token.c
//
//  Created by Shady Khalifa on 08/01/18.
//  Copyright (c) 2018 Shady Khalifa. All rights reserved.
//
#include "token.h"

const char *token_name (int token) {
	switch (token) {
		// keywords
		case Fun: return "func";
		case True: return "1";
		case False: return "0";
		case If: return "if";
		case Else: return "else";
		case Return: return "return";
		case While: return "while";
		case Enum: return "enum";
		// operators
		case Add: return "+";
		case Sub: return "-";
		case Div: return "/";
		case Mul: return "*";
		case Mod: return "%";
		case Assign: return "=";
		case Lt: return "<";
		case Gt: return ">";
		case Le: return "<=";
		case Ge: return ">=";
		case Inc: return "+=";
		case Dec: return "-=";
		case Lan: return "&&";
		case Lor: return "||";
		case Eq: return "==";
		case Ne: return "!=";
		case Shl: return "<<";
		case Shr: return ">>";
		case And: return "&";
		case Or: return "|";
		case Xor: return "^";
	}

	// should never reach this point
	return "UNRECOGNIZED TOKEN";
}
