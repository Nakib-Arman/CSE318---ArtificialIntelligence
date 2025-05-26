%option noyywrap

%x DEFINE
%x TYPE
%x STRING
%x CHAR

%{

#include<bits/stdc++.h>
using namespace std;

string str="";

%}

letter [a-zA-Z]
digit [0-9]
alphanumeric [_a-zA-Z0-9]


%%

"#define" {
    BEGIN DEFINE;
    str+=yytext;
}

<DEFINE>(_)?{letter}+{alphanumeric}* {
    BEGIN TYPE;
    str+=yytext;
}
<TYPE>"\'"{letter}"\'" {
    str+=yytext;
    str+="(MACRO WITH CHAR) found.";
    BEGIN INITIAL;
}

<TYPE>"\"" {
    BEGIN STRING;
}
<STRING>. {
    str+=yytext;
}
<STRING>"\"" {
    str+=yytext;
    str+=" (MACRO WITH STRING) found.";
    BEGIN INITIAL;
}

<TYPE>{digit}+ {
    str+=yytext;
}



%%

int main(int argc, char **argv){
    /* freopen("output_log.txt", "w", stdout);
    f1 = fopen("output_token.txt","w");
    if (argc != 2) {
        printf("No input file provided");
        fprintf(f1,"No input file provided");
        return 1;
    }
    char* filename = argv[1];
    FILE *input_file = fopen(filename,"r");
    if(input_file == NULL){
        perror("Error opening input file");
        return 1;
    } */

    yyin = stdin;
    yylex();
    fclose(yyin);
    /* fclose(f1); */

    return 0;
}