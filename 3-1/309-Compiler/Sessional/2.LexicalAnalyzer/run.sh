#!/usr/bin/bash

flex main.l
g++ lex.yy.c
./a.out
# diff output_token.txt output/input1_token.txt