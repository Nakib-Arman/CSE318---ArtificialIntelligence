#!/usr/bin/bash

flex main.l
g++ lex.yy.c
./a.out