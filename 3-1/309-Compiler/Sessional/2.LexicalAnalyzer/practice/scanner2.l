%option noyywrap

%{
#include<stdio.h>

%}

letter [a-zA-Z]
digit [0-9]

%%

[ \t\v\n] {}
"if" {printf("<%s>","IF");}
"else" {printf("<%s>","ELSE");}
{letter}+[{digit}{letter}]* {printf("<%s,%s>","ID",yytext);}
{digit}+ {printf("<%s,%s>","CONST_INT",yytext);}
{digit}+.{digit}+ {printf("<%s,%s>","CONST_FLOAT",yytext);}
";" {printf("<%s>","SEMICOLON");}
"(" {printf("<%s,%s>","LPAREN",yytext);}
")" {printf("<%s,%s>","RPAREN",yytext);}
"{" {printf("<%s,%s>","LCURL",yytext);}
"}" {printf("<%s,%s>","RCURL",yytext);}
[+-] {printf("<%s,%s>","ADDOP",yytext);}
["] {printf("<%s,%s>","DELIM",yytext);}
"==" {printf("<%s,%s>","RELOP","EQ");}
">=" {printf("<%s,%s>","RELOP","GE");}
"<=" {printf("<%s,%s>","RELOP","LE");}
">" {printf("<%s,%s>","RELOP","GT");}
"<" {printf("<%s,%s>","RELOP","LT");}
"=" {printf("<%s>","ASSIGN");}
. {}

%%

int main(){
    FILE *input_file = fopen("scanner.txt","r");
    yyin = input_file;
    yylex();
    fclose(yyin);
    return 0;
}