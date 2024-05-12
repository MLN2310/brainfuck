# brainfuck

a brainfuck compiler

## requirement

- PC with x86-64 architecture and Linux OS
- clang or gcc
- llvm

## usage

1. compile main.cpp
2. cat < source file name > | ./a.out | llc > assembly.s
3. clang assembly.s -o < file name >.out