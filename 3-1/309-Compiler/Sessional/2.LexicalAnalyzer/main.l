%option noyywrap

%x String

%{

#include<stdio.h>
#include<string.h>
#include "../1.SymbolTable/2105128_SymbolTable.cpp"

// SymbolTable* symboltable = new SymbolTable(7,&HashFunction::SDBMHash);
int line_count=1;

void print_char_constant(char* ch){
    if(!strcmp(ch,"'\\n'")) printf("<CHAR_CONST, \n> ");
    else if(!strcmp(ch,"'\\t'")) printf("<CHAR_CONST, \t> ");
    else if(!strcmp(ch,"'\\\\'")) printf("<CHAR_CONST, \\> ");
    else if(!strcmp(ch,"'\\''")) printf("<CHAR_CONST, \'> ");
    else if(!strcmp(ch,"'\\a'")) printf("<CHAR_CONST, \a> ");
    else if(!strcmp(ch,"'\\f'")) printf("<CHAR_CONST, \f> ");
    else if(!strcmp(ch,"'\\r'")) printf("<CHAR_CONST, \n> ");
    else if(!strcmp(ch,"'\\b'")) printf("<CHAR_CONST, \b> ");
    else if(!strcmp(ch,"'\\v'")) printf("<CHAR_CONST, \v> ");
    else printf("<CHAR_CONST, %c> ", ch[1]); 
}

void print_float(char* ch){
    for (int i=0;ch[i]!='\0';i++){
        ch[i]=tolower((unsigned char)ch[i]);
    }
    printf("<CONST_FLOAT, %s> ",ch);
}


%}

letter [a-zA-Z]
digit [0-9]
alphanumeric [_a-zA-Z0-9]
esc_sequence [nt\'"afrbvO]

%%

[ \t\v\n] {}

"if"       {printf("<%s> ","IF");}
"for"      {printf("<%s> ","FOR");}
"do"       {printf("<%s> ","DO");}
"int"      {printf("<%s> ","INT");}
"float"    {printf("<%s> ","FLOAT");}
"void"     {printf("<%s> ","VOID");}
"switch"   {printf("<%s> ","SWITCH");}
"default"  {printf("<%s> ","DEFAULT");}
"else"     {printf("<%s> ","ELSE");}
"while"    {printf("<%s> ","WHILE");}
"break"    {printf("<%s> ","BREAK");} 
"char"     {printf("<%s> ","CHAR");}
"double"   {printf("<%s> ","DOUBLE");}
"return"   {printf("<%s> ","RETURN");}
"case"     {printf("<%s> ","CASE");}
"continue" {printf("<%s> ","CONTINUE");}
"goto"     {printf("<%s> ","GOTO");}
"long"     {printf("<%s> ","LONG");}
"short"    {printf("<%s> ","SHORT");}
"static"   {printf("<%s> ","STATIC");}
"unsigned" {printf("<%s> ","UNSIGNED");}


{digit}+ {printf("<%s, %s> ","CONST_INT",yytext);}
{digit}+(\.{digit}+)?(E[+-]?{digit}+)? {print_float(yytext);}
(\'(\\)?{letter}\') {print_char_constant(yytext);}


"++"    | 
"--" {printf("<INCOP, %s> ",yytext);}
"+"     | 
"-" {printf("<ADDOP, %s> ",yytext);}
"*"     | 
"/"     | 
"%" {printf("<MULOP, %s> ",yytext);}
"<="    | 
">="    | 
"=="    |   
"!=" {printf("<RELOP, %s> ",yytext);}
"<"     | 
">"  {printf("<RELOP, %s> ",yytext);}
"=" {printf("<ASSIGNOP, %s> ",yytext);}
"!" {printf("<NOT, %s> ",yytext);}
"&&"    | 
"||" {printf("<LOGICOP, %s> ",yytext);}
"(" {printf("<LPAREN, %s> ",yytext);}
")" {printf("<RPAREN, %s> ",yytext);}
"{" {printf("<LCURL, %s> ",yytext);}
"}" {printf("<RCURL, %s> ",yytext);}
"[" {printf("<LTHIRD, %s> ",yytext);}
"]" {printf("<RTHIRD, %s> ",yytext);}
"," {printf("<COMMA, %s> ",yytext);}
";" {printf("<SEMICOLON, %s> ",yytext);}


(_)?{letter}+{alphanumeric}* {printf("<ID, %s> ",yytext);}


"\"" {
    BEGIN String;
    printf("\nString begins\n");
}
<String>(\\){esc_sequence} {printf("%s",yytext);}
<String> (\\) {printf("backslash");}
<String>"\"" {
    printf("\nstring ends\n");
    BEGIN INITIAL;
}

<<EOF>> {return 0;}
. {}

%%

int main(){
    FILE *input_file = fopen("input/input2.txt","r");

    yyin = input_file;
    yylex();
    fclose(yyin);
    return 0;
}