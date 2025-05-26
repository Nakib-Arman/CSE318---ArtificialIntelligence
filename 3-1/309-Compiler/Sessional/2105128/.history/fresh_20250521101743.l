%option noyywrap

%x Char_const
%x String
%x Single_line_comment
%x Multi_line_comment

%{

#include<stdio.h>
#include<string.h>
#include "../1.SymbolTable/2105128_SymbolTable.cpp"


%}

letter [a-zA-Z]
digit [0-9]
alphanumeric [_a-zA-Z0-9]


%%


{digit}+ {
    inserted = symboltable->insert(yytext,"CONST_INT","");
    printf("Line no %d: Token <CONST_INT> Lexeme %s found\n\n",line_count,yytext);
    if(inserted.second.first ==0 && inserted.second.second ==0) symboltable->print_all_scope_nonempty_indices();
    else printf("< %s : CONST_INT > already exists in ScopeTable# %s at position %d, %d\n\n",yytext,inserted.first.c_str(),inserted.second.first,inserted.second.second);
    fprintf(f1,"<%s, %s> ","CONST_INT",yytext);
}
{digit}+(\.{digit}+)?E[+-]?{digit}+(\.){digit}*((\.){digit}*)* {
    err_count++;
    printf("Error at line no %d: Ill formed number %s\n\n\n",line_count,yytext);
}
({digit}+)?(\.){digit}*(\.).* {
    err_count++;
    printf("Error at line no %d: Too many decimal points %s\n\n\n",line_count,yytext);
}

({digit}+)?(\.{digit}+)?(E[+-]?{digit}+)? {
    inserted = print_float(yytext,line_count);
    if(inserted.second.first == 0 && inserted.second.second == 0) symboltable->print_all_scope_nonempty_indices();
    else printf("< %s : CONST_FLOAT > already exists in ScopeTable# %s at position %d, %d\n\n",yytext,inserted.first.c_str(),inserted.second.first,inserted.second.second);
}


{digit}+{alphanumeric}+ {
    err_count++;
    printf("Error at line no %d: Invalid prefix on ID or invalid suffix on Number %s\n\n",line_count,yytext);
}
(_)?{letter}+{alphanumeric}* {
    inserted = symboltable->insert(yytext,"ID","");
    fprintf(f1,"<ID, %s> ",yytext);
    printf("Line no %d: Token <ID> Lexeme %s found\n\n",line_count,yytext);
    if(inserted.second.first == 0 && inserted.second.second == 0) symboltable->print_all_scope_nonempty_indices();
    else printf("< %s : ID > already exists in ScopeTable# %s at position %d, %d\n\n",yytext,inserted.first.c_str(),inserted.second.first,inserted.second.second);
}

<<EOF>> {
    symboltable->print_all_scope_nonempty_indices();
    printf("Total lines: %d\n",line_count);
    printf("Total errors: %d\n",err_count);
    return 0;
}
. {
    err_count++;
    printf("Error at line no %d: Unrecognized character %s\n\n",line_count,yytext);
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