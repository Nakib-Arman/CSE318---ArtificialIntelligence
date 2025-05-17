#!/usr/bin/bash

flex main.l
g++ lex.yy.c

./a.out input/input1.txt
diff output_token.txt output/input1_token.txt
diff output_log.txt output/input1_log.txt

# ./a.out input/input2.txt
# diff output_token.txt output/input2_token.txt
# diff output_log.txt output/input2_log.txt

# ./a.out input/input3.txt
# diff output_token.txt output/input3_token.txt
# diff output_log.txt output/input3_log.txt