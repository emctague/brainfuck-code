# Brainfuck Code

This project contains various small, brainfuck-related projects.
These include my various implementations of compilers and interpreters, as well
as other utilities.

## Current Working Projects

 * Compiler to convert brainfuck source code to native code (via `g++`).
 * Complete native interpreter of brainfuck.
 * Complete JavaScript library to interpret brainfuck.

## Native Compiler

The brainfuck native compiler source code is located in `cfuck.cpp`.

It can be compiled with:

```
g++ cfuck.cpp -o cf --std=c++11
```

Usage:

```
cf [source file] [destination file]
```

Of course, this program depends on the `g++` command being available on the
system, as it generates a temporary C++ file and calls this command on it to
produce the final output.

## Native (C++) Interpreter

This is a complete, lightweight brainfuck interpreter, at just over 120 lines
of code (including comments.) Although it currently has no command-line
interface, copying the function definitions from `brainfuck.cpp` would
definitely give you a decent BrainFuck interpreter command:

```
std::string brainfuck(std::string program, std::string input);
```

## JavaScript Interpreter

Copying the source from `brainfuck.js` would leave you with a JS-based
brainfuck interpreter with a similar function to the C++ version:

```
var output = brainfuck(program, input);
```

## Licensing

All of these programs are free to use under the terms of the MIT license. See
LICENSE for more details.

Copyright (C) 2017 Ethan McTague
