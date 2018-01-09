# Jax

minimal C-interpreter to play with.
![JAXLOGO](https://i.imgur.com/aMvkxnX.png "JAX Logo")

## A Story

OK, I was - *as You* - heedful about how compilers/interpreters works
What's a VM ? Bytecode ! .
All these question comes to my head.
After that I Would to say. It was so **COOL** to write a **VM** and an interpreter.

## Project Structer

```bash
.
├── build
│   └── jax <-- Binary
├── Makefile
├── src
│   ├── glob.h <-- Shared Bettween Project
│   ├── lexer  <-- Lexer , It will used to read the code and convert it to tokens
│   │   ├── lexer.c
│   │   ├── lexer.h
│   │   ├── token.c
│   │   └── token.h
│   ├── main.c <-- Main Program
│   ├── parser <-- It will parse tokens and Convert it into VM Instructions
│   │   ├── parser.c
│   │   └── parser.h
│   ├── utils
│   │   ├── debug.c
│   │   └── debug.h
│   └── vm <-- It will execute Instructions
│       ├── vm.c
│       └── vm.h
└── test
    ├── math.jax
    └── test.jax

```

### Prerequisites

Make and GCC installed.

### Building

```bash
git clone https://github.com/shekohex/jax.git
cd /jax
make build
```

## Why you should care about compiler theory?

Because it is **COOL**!

And it is very useful. Programs are built to do something for us, when they are used to translate some forms of data into another form, we can call them compiler. Thus by learning some compiler theory we are trying to master a very powerful technique of solving problems. Isn't that cool enough to you?

People used to say understanding how compiler works would help you to write better code. Some would argue that modern compilers are so good at optimization that you should not care any more. Well, that's true, most people don't need to learn compiler theory only to improve the efficency of the code. And by most people, I mean you!

## Contributing

This Project was Just for Learning Purpose, but if you want to contribute
you are welcome with this project, just contact me or make a PR

## Good Resources

* [Let’s Build a Compiler](http://compilers.iecc.com/crenshaw/): a very good
    tutorial of building a compiler for fresh starters.

* [Lemon Parser Generator](http://www.hwaci.com/sw/lemon/): the parser
    generator that is used in SQLite. Good to read if you want to understand
    compiler theory with code.

* [Write a C-interpreter](https://github.com/lotabout/write-a-C-interpreter/tree/master/tutorial/en) :  series of articles of a tutorials of building a C compiler from scratch.

### Thanks to

*  [Jinzhou Zhang](https://github.com/lotabout): Who made a great series of articles on how to write a C compiler from scratch.

*   [Robert Swierczek](https://github.com/rswier) : created `c4` a C-interpreter in just four functions

In the end, I am human with a general level, there will be inevitably wrong
with the articles and codes(also my English). Feel free to correct me!

Hope you enjoy it.