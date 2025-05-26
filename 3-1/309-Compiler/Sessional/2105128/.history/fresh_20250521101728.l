%option noyywrap

%x Char_const
%x String
%x Single_line_comment
%x Multi_line_comment

%{

#include<stdio.h>
#include<string.h>
#include "../1.SymbolTable/2105128_SymbolTable.cpp"

FILE *f1;
SymbolTable* symboltable = new SymbolTable(7,&HashFunction::sdbmHash);
int line_count=1;
int initial_line;
int err_count=0;
string str1="",str2="";
string cmnt="";
pair<string,pair<int,int>> inserted;

bool print_char_constant(string ch,int line_count){
    if(ch == "'\\n'"){
        fprintf(f1,"<CONST_CHAR, \n> ");
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, \n>\n\n",line_count,ch.c_str());
    }
    else if(ch == "'\\t'"){
        fprintf(f1,"<CONST_CHAR, \t> ");
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, \t>\n\n",line_count,ch.c_str());
    }
    else if(ch == "'\\\\'"){
        fprintf(f1,"<CONST_CHAR, \\> ");
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, \\>\n\n",line_count,ch.c_str());
    }
    else if(ch == "'\\''"){
        fprintf(f1,"<CONST_CHAR, \'> ");
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, \'>\n\n",line_count,ch.c_str());
    }
    else if(ch == "'\\a'"){
        fprintf(f1,"<CONST_CHAR, \a> ");
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, \a>\n\n",line_count,ch.c_str());
    }
    else if(ch == "'\\f'"){
        fprintf(f1,"<CONST_CHAR, \f> ");
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, \f>\n\n",line_count,ch.c_str());
    }
    else if(ch == "'\\r'"){
        fprintf(f1,"<CONST_CHAR, \r> ");
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, \r>\n\n",line_count,ch.c_str());
    }
    else if(ch == "'\\b'"){
        fprintf(f1,"<CONST_CHAR, \b> ");
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, \b>\n\n",line_count,ch.c_str());
    }
    else if(ch == "'\\v'"){
        fprintf(f1,"<CONST_CHAR, \v> ");
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, \v>\n\n",line_count,ch.c_str());
    }
    else if(ch == "'\\0'"){
        fprintf(f1,"<CONST_CHAR, \0> ");
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, \0>\n\n",line_count,ch.c_str());
    }
    else if(ch[1] == '\\' && ch[3] == '\''){
        fprintf(f1,"CONST_CHAR, %c> ",ch[2]);
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, %c>\n\n",line_count,ch.c_str(),ch[2]);
    }
    else if((ch[0] == '\'') && (ch[2] =='\'')){
        fprintf(f1,"<CONST_CHAR, %c> ", ch[1]); 
        printf("Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, %c>\n\n",line_count,ch.c_str(),ch[1]);
    }
    else{
        err_count++;
        printf("Error at line no %d: Multi character constant error %s\n\n\n",line_count,ch.c_str());
        return false;
    }
    return true;
}

void print_escape_sequence(char* ch,string& str){
    if(!strcmp(ch,"\\\"")){
        str=str+"\"";
    }
    else if(!strcmp(ch,"\\n")){
        str=str+"\n";
    }
    else if(!strcmp(ch,"'\\t'")){
        str=str+"\t";
    }
    else if(!strcmp(ch,"'\\\\'")){
        str=str+"\\";
    }
    else if(!strcmp(ch,"'\\''")){
        str=str+"\'";
    }
    else if(!strcmp(ch,"'\\a'")){
        str=str+"\a";
    }
    else if(!strcmp(ch,"'\\f'")){
        str=str+"\f";
    }
    else if(!strcmp(ch,"'\\r'")){
        str=str+"\n";
    }
    else if(!strcmp(ch,"'\\b'")){
        str=str+"\b";
    }
    else if(!strcmp(ch,"'\\v'")){
        str=str+"\v";
    }
    else if(!strcmp(ch,"'\\0'")){
        str=str+"\0";
    }
}

pair<string,pair<int,int>> print_float(char* ch,int line_count){
    // for (int i=0;ch[i]!='\0';i++){
    //     ch[i]=tolower((unsigned char)ch[i]);
    // }
    fprintf(f1,"<CONST_FLOAT, %s> ",ch);
    printf("Line no %d: Token <CONST_FLOAT> Lexeme %s found\n\n",line_count,ch);
    inserted = symboltable->insert(ch,"CONST_FLOAT","");
    return inserted;
}


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