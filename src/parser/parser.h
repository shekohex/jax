//
//  parser.h
//
//  Created by Shady Khalifa on 9/01/18.
//  Copyright (c) 2018 Shady Khalifa. All rights reserved.
//

#ifndef PARSER_H
#define PARSER_H

void    match(int tkn);          // it will try to parse a token
void    global_declaration(); 
void    variable_declaration(int class);
void    enum_declaration();
void    function_declaration();
void    function_body();
void    function_parameter();
void    statement();
void    expression(int level);

#endif // PARSER_H