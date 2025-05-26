#!/usr/bin/bash

flex fresh.l
g++ lex.yy.c
./a.out