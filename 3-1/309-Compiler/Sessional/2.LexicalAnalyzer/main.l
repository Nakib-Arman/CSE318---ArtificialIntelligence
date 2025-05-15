%option noyywrap

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
int initial_line=0;
string str1="",str2="";
string cmnt="";
bool inserted = false;

void print_char_constant(char* ch,int line_count){
    if(!strcmp(ch,"'\\n'")){
        fprintf(f1,"<CHAR_CONST, \n> ");
        printf("\nLine no %d: Token <CONST_CHAR> Lexeme %sfound --><CHAR_CONST, \n> \n",line_count,ch);
    }
    else if(!strcmp(ch,"'\\t'")){
        fprintf(f1,"<CHAR_CONST, \t> ");
        printf("\nLine no %d: Token <CONST_CHAR> Lexeme %sfound --><CHAR_CONST, \t> \n",line_count,ch);
    }
    else if(!strcmp(ch,"'\\\\'")){
        fprintf(f1,"<CHAR_CONST, \\> ");
        printf("\nLine no %d: Token <CONST_CHAR> Lexeme %sfound --><CHAR_CONST, \\> \n",line_count,ch);
    }
    else if(!strcmp(ch,"'\\''")){
        fprintf(f1,"<CHAR_CONST, \'> ");
        printf("\nLine no %d: Token <CONST_CHAR> Lexeme %sfound --><CHAR_CONST, \'> \n",line_count,ch);
    }
    else if(!strcmp(ch,"'\\a'")){
        fprintf(f1,"<CHAR_CONST, \a> ");
        printf("\nLine no %d: Token <CONST_CHAR> Lexeme %sfound --><CHAR_CONST, \a> \n",line_count,ch);
    }
    else if(!strcmp(ch,"'\\f'")){
        fprintf(f1,"<CHAR_CONST, \f> ");
        printf("\nLine no %d: Token <CONST_CHAR> Lexeme %sfound --><CHAR_CONST, \f> \n",line_count,ch);
    }
    else if(!strcmp(ch,"'\\r'")){
        fprintf(f1,"<CHAR_CONST, \n> ");
        printf("\nLine no %d: Token <CONST_CHAR> Lexeme %sfound --><CHAR_CONST, \r> \n",line_count,ch);
    }
    else if(!strcmp(ch,"'\\b'")){
        fprintf(f1,"<CHAR_CONST, \b> ");
        printf("\nLine no %d: Token <CONST_CHAR> Lexeme %sfound --><CHAR_CONST, \b> \n",line_count,ch);
    }
    else if(!strcmp(ch,"'\\v'")){
        fprintf(f1,"<CHAR_CONST, \v> ");
        printf("\nLine no %d: Token <CONST_CHAR> Lexeme %sfound --><CHAR_CONST, \v> \n",line_count,ch);
    }
    else{
        fprintf(f1,"<CHAR_CONST, %c> ", ch[1]); 
        printf("\nLine no %d: Token <CONST_CHAR> Lexeme %s found --> <CHAR_CONST, %c> \n",line_count,ch,ch[1]);
    }
}

void print_escape_sequence(char* ch,string& str){
    if(!strcmp(ch,"\\\"")){
        fprintf(f1,"\"");
        str=str+"\"";
    }
    else if(!strcmp(ch,"\\n")){
        fprintf(f1,"\n");
        str=str+"\n";
    }
    else if(!strcmp(ch,"'\\t'")){
        fprintf(f1,"\t");
        str=str+"\t";
    }
    else if(!strcmp(ch,"'\\\\'")){
        fprintf(f1,"\\");
        str=str+"\\";
    }
    else if(!strcmp(ch,"'\\''")){
        fprintf(f1,"\'");
        str=str+"\'";
    }
    else if(!strcmp(ch,"'\\a'")){
        fprintf(f1,"\a");
        str=str+"\a";
    }
    else if(!strcmp(ch,"'\\f'")){
        fprintf(f1,"\f");
        str=str+"\f";
    }
    else if(!strcmp(ch,"'\\r'")){
        fprintf(f1,"\n");
        str=str+"\n";
    }
    else if(!strcmp(ch,"'\\b'")){
        fprintf(f1,"\b");
        str=str+"\b";
    }
    else if(!strcmp(ch,"'\\v'")){
        fprintf(f1,"\v");
        str=str+"\v";
    }
}

void print_float(char* ch,int line_count){
    for (int i=0;ch[i]!='\0';i++){
        ch[i]=tolower((unsigned char)ch[i]);
    }
    fprintf(f1,"<CONST_FLOAT, %s> ",ch);
    printf("\nLine no %d: Token <CONST_FLOAT> Lexeme %s found\n",line_count,ch);
}


%}

letter [a-zA-Z]
digit [0-9]
alphanumeric [_a-zA-Z0-9]
backslash "\\"

%%

[ \t\v] {}
"\n" {line_count++;}

"if"       {
    fprintf(f1,"<%s> ","IF");
    printf("\nLine no %d: Token <IF> Lexeme %s found\n",line_count,yytext);
}
"for"      {
    fprintf(f1,"<%s> ","FOR");
    printf("\nLine no %d: Token <FOR> Lexeme %s found\n",line_count,yytext);
}
"do"       {
    fprintf(f1,"<%s> ","DO");
    printf("\nLine no %d: Token <DO> Lexeme %s found\n",line_count,yytext);  
}
"int"      {
    fprintf(f1,"<%s> ","INT");
    printf("\nLine no %d: Token <INT> Lexeme %s found\n",line_count,yytext);
}
"float"    {
    fprintf(f1,"<%s> ","FLOAT");
    printf("\nLine no %d: Token <FLOAT> Lexeme %s found\n",line_count,yytext);
}
"void"     {
    fprintf(f1,"<%s> ","VOID");
    printf("\nLine no %d: Token <VOID> Lexeme %s found\n",line_count,yytext);
}
"switch"   {
    fprintf(f1,"<%s> ","SWITCH");
    printf("\nLine no %d: Token <SWITCH> Lexeme %s found\n",line_count,yytext);
}
"default"  {
    fprintf(f1,"<%s> ","DEFAULT");
    printf("\nLine no %d: Token <DEFAULT> Lexeme %s found\n",line_count,yytext);
}
"else"     {
    fprintf(f1,"<%s> ","ELSE");
    printf("\nLine no %d: Token <ELSE> Lexeme %s found\n",line_count,yytext);
}
"while"    {
    fprintf(f1,"<%s> ","WHILE");
    printf("\nLine no %d: Token <WHILE> Lexeme %s found\n",line_count,yytext);
}
"break"    {
    fprintf(f1,"<%s> ","BREAK");
    printf("\nLine no %d: Token <BREAK> Lexeme %s found\n",line_count,yytext);
} 
"char"     {
    fprintf(f1,"<%s> ","CHAR");
    printf("\nLine no %d: Token <CHAR> Lexeme %s found\n",line_count,yytext);
}
"double"   {
    fprintf(f1,"<%s> ","DOUBLE");
    printf("\nLine no %d: Token <DOUBLE> Lexeme %s found\n",line_count,yytext);
}
"return"   {
    fprintf(f1,"<%s> ","RETURN");
    printf("\nLine no %d: Token <RETURN> Lexeme %s found\n",line_count,yytext);
}
"case"     {
    fprintf(f1,"<%s> ","CASE");
    printf("\nLine no %d: Token <CASE> Lexeme %s found\n",line_count,yytext);
}
"continue" {
    fprintf(f1,"<%s> ","CONTINUE");
    printf("\nLine no %d: Token <CONTINUE> Lexeme %s found\n",line_count,yytext);
}
"goto"     {
    fprintf(f1,"<%s> ","GOTO");
    printf("\nLine no %d: Token <GOTO> Lexeme %s found\n",line_count,yytext);
}
"long"     {
    fprintf(f1,"<%s> ","LONG");
    printf("\nLine no %d: Token <LONG> Lexeme %s found\n",line_count,yytext);
}
"short"    {
    fprintf(f1,"<%s> ","SHORT");
    printf("\nLine no %d: Token <SHORT> Lexeme %s found\n",line_count,yytext);
}
"static"   {
    fprintf(f1,"<%s> ","STATIC");
    printf("\nLine no %d: Token <STATIC> Lexeme %s found\n",line_count,yytext);
}
"unsigned" {
    fprintf(f1,"<%s> ","UNSIGNED");
    printf("\nLine no %d: Token <UNSIGNED> Lexeme %s found\n",line_count,yytext);
}


{digit}+ {
    inserted = symboltable->insert(yytext,"CONST_INT","");
    printf("\nLine no %d: Token <CONST_INT> Lexeme %s found\n",line_count,yytext);
    if(inserted) symboltable->print_all_scope_nonempty_indices();
    fprintf(f1,"<%s, %s> ","CONST_INT",yytext);
}
{digit}+(\.{digit}+)?(E[+-]?{digit}+)? {
    inserted = symboltable->insert(yytext,"CONST_FLOAT","");
    print_float(yytext,line_count);
    if(inserted) symboltable->print_all_scope_nonempty_indices();
}
(\'(\\)?{letter}\') {
    inserted = symboltable->insert(yytext,"CONST_CHAR","");
    print_char_constant(yytext,line_count);
    if(inserted) symboltable->print_all_scope_nonempty_indices();
}


"++"    | 
"--" {
    fprintf(f1,"<INCOP, %s> ",yytext);
    printf("\nLine no %d: Token <INCOP> Lexeme %s found\n",line_count,yytext);
}
"+"     | 
"-" {
    fprintf(f1,"<ADDOP, %s> ",yytext);
    printf("\nLine no %d: Token <ADDOP> Lexeme %s found\n",line_count,yytext);
}
"*"     | 
"/"     | 
"%" {
    fprintf(f1,"<MULOP, %s> ",yytext);
    printf("\nLine no %d: Token <MULOP> Lexeme %s found\n",line_count,yytext);
}
"<="    | 
">="    | 
"=="    |   
"!=" {
    fprintf(f1,"<RELOP, %s> ",yytext);
    printf("\nLine no %d: Token <RELOP> Lexeme %s found\n",line_count,yytext);
}
"<"     | 
">"  {
    fprintf(f1,"<RELOP, %s> ",yytext);
    printf("\nLine no %d: Token <RELOP> Lexeme %s found\n",line_count,yytext);
}
"=" {
    fprintf(f1,"<ASSIGNOP, %s> ",yytext);
    printf("\nLine no %d: Token <ASSIGNOP> Lexeme %s found\n",line_count,yytext);
}
"!" {
    fprintf(f1,"<NOT, %s> ",yytext);
    printf("\nLine no %d: Token <NOT> Lexeme %s found\n",line_count,yytext);
}
"&&"    | 
"||" {
    fprintf(f1,"<LOGICOP, %s> ",yytext);
    printf("\nLine no %d: Token <LOGICOP> Lexeme %s found\n",line_count,yytext);
}
"(" {
    fprintf(f1,"<LPAREN, %s> ",yytext);
    printf("\nLine no %d: Token <LPAREN> Lexeme %s found\n",line_count,yytext);
}
")" {
    fprintf(f1,"<RPAREN, %s> ",yytext);
    printf("\nLine no %d: Token <RPAREN> Lexeme %s found\n",line_count,yytext);
}
"{" {
    symboltable->EnterScope();
    fprintf(f1,"<LCURL, %s> ",yytext);
    printf("\nLine no %d: Token <LCURL> Lexeme %s found\n",line_count,yytext);
}
"}" {
    symboltable->ExitScope();
    fprintf(f1,"<RCURL, %s> ",yytext);
    printf("\nLine no %d: Token <RCURL> Lexeme %s found\n",line_count,yytext);
}
"[" {
    fprintf(f1,"<LTHIRD, %s> ",yytext);
    printf("\nLine no %d: Token <LTHIRD> Lexeme %s found\n",line_count,yytext);
}
"]" {
    fprintf(f1,"<RTHIRD, %s> ",yytext);
    printf("\nLine no %d: Token <RTHIRD> Lexeme %s found\n",line_count,yytext);
}
"," {
    fprintf(f1,"<COMMA, %s> ",yytext);
    printf("\nLine no %d: Token <COMMA> Lexeme %s found\n",line_count,yytext);
}
";" {
    fprintf(f1,"<SEMICOLON, %s> ",yytext);
    printf("\nLine no %d: Token <SEMICOLON> Lexeme %s found\n",line_count,yytext);
}


(_)?{letter}+{alphanumeric}* {
    inserted = symboltable->insert(yytext,"ID","");
    fprintf(f1,"<ID, %s> ",yytext);
    printf("\nLine no %d: Token <ID> Lexeme %s found\n",line_count,yytext);
    if(inserted) symboltable->print_all_scope_nonempty_indices();
}


"\"" {
    BEGIN String;
    fprintf(f1,"<STRING, \"");
    initial_line = line_count;
    str1="";
    str2="";
    str1=str1+yytext;
    str2=str2+"\"";
}
<String>"\\\n" {
    line_count++;
    str1=str1+yytext;  
    str2=str2+""; 
}
<String>{backslash}[nt'"afrbv\\] {
    str1=str1+yytext;
    print_escape_sequence(yytext,str2);
}
<String>"\"" {
    fprintf(f1,"\"> ");
    str1=str1+yytext;
    str2=str2+yytext;
    printf("\nLine no %d: Token <STRING> Lexeme %s found --> <STRING, %s> \n",initial_line,str1.c_str(),str2.c_str());
    BEGIN INITIAL;
}
<String>. {
    fprintf(f1,"%s",yytext);
    str1=str1+yytext;
    str2=str2+yytext;    
}


"//" {
    BEGIN Single_line_comment;
    cmnt = "";
    cmnt = cmnt+yytext;
    initial_line = line_count;
}
<Single_line_comment>"\\\n" {
    line_count++;
    cmnt = cmnt+yytext;
}
<Single_line_comment>"\n" {
    line_count++;
    printf("\nLine no %d: Token <COMMENT> Lexeme %s found\n",initial_line,cmnt.c_str());
    BEGIN INITIAL;
} 
<Single_line_comment>. {
    cmnt = cmnt+yytext;
}

"/*" {
    BEGIN Multi_line_comment;
    cmnt = "";
    cmnt = cmnt+yytext;
    initial_line = line_count;
}
<Multi_line_comment>"*/" {
    printf("\nLine no %d: Token <COMMENT> Lexeme %s*/ found\n",initial_line,cmnt.c_str());
    BEGIN INITIAL;
}
<Multi_line_comment>"\n" {
    line_count++;
    cmnt = cmnt+yytext;
}
<Multi_line_comment>. {
    cmnt = cmnt+yytext;
}


<<EOF>> {return 0;}
. {}

%%

int main(){
    FILE *input_file = fopen("input/input1.txt","r");
    freopen("output_log.txt", "w", stdout);
    f1 = fopen("output_token.txt","w");
    /* f2 = fopen("output_log.txt","w"); */

    yyin = input_file;
    yylex();
    fclose(yyin);
    fclose(f1);
    /* fclose(f2); */
    return 0;
}