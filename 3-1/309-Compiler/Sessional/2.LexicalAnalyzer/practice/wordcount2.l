%option noyywrap

%{
#include<stdio.h>

int word_count=0;
int digit_count=0;
int line_count=1;

void IncWC(char* str){
    word_count++;
    printf("%s word found again\n",str);
}
%}

letter [a-zA-Z]
digit [0-9]


%%

[ \t\v] {}
{letter}+ {IncWC(yytext);}
{digit}+(.{digit}+)?([E][+-]?{digit}+)? {digit_count++; printf("%s digit found in the file\n",yytext);}
[\n] {line_count++;}
<<EOF>> {printf("Word count: %d\nDigit count: %d\nLine count: %d",word_count,digit_count,line_count); return 0;}
. {}

%%

int main(){
    FILE *input_file = fopen("wordcount.txt","r");

    yyin = input_file;
    yylex();
    fclose(yyin);
    return 0;
}