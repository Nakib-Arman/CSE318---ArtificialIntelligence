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

[ \t\v] {}
"\n" {line_count++;}

"if"       {
    fprintf(f1,"<%s> ","IF");
    printf("Line no %d: Token <IF> Lexeme %s found\n\n",line_count,yytext);
}
"for"      {
    fprintf(f1,"<%s> ","FOR");
    printf("Line no %d: Token <FOR> Lexeme %s found\n\n",line_count,yytext);
}
"do"       {
    fprintf(f1,"<%s> ","DO");
    printf("Line no %d: Token <DO> Lexeme %s found\n\n",line_count,yytext);  
}
"int"      {
    fprintf(f1,"<%s> ","INT");
    printf("Line no %d: Token <INT> Lexeme %s found\n\n",line_count,yytext);
}
"float"    {
    fprintf(f1,"<%s> ","FLOAT");
    printf("Line no %d: Token <FLOAT> Lexeme %s found\n\n",line_count,yytext);
}
"void"     {
    fprintf(f1,"<%s> ","VOID");
    printf("Line no %d: Token <VOID> Lexeme %s found\n\n",line_count,yytext);
}
"switch"   {
    fprintf(f1,"<%s> ","SWITCH");
    printf("Line no %d: Token <SWITCH> Lexeme %s found\n\n",line_count,yytext);
}
"default"  {
    fprintf(f1,"<%s> ","DEFAULT");
    printf("Line no %d: Token <DEFAULT> Lexeme %s found\n\n",line_count,yytext);
}
"else"     {
    fprintf(f1,"<%s> ","ELSE");
    printf("Line no %d: Token <ELSE> Lexeme %s found\n\n",line_count,yytext);
}
"while"    {
    fprintf(f1,"<%s> ","WHILE");
    printf("Line no %d: Token <WHILE> Lexeme %s found\n\n",line_count,yytext);
}
"break"    {
    fprintf(f1,"<%s> ","BREAK");
    printf("Line no %d: Token <BREAK> Lexeme %s found\n\n",line_count,yytext);
} 
"char"     {
    fprintf(f1,"<%s> ","CHAR");
    printf("Line no %d: Token <CHAR> Lexeme %s found\n\n",line_count,yytext);
}
"double"   {
    fprintf(f1,"<%s> ","DOUBLE");
    printf("Line no %d: Token <DOUBLE> Lexeme %s found\n\n",line_count,yytext);
}
"return"   {
    fprintf(f1,"<%s> ","RETURN");
    printf("Line no %d: Token <RETURN> Lexeme %s found\n\n",line_count,yytext);
}
"case"     {
    fprintf(f1,"<%s> ","CASE");
    printf("Line no %d: Token <CASE> Lexeme %s found\n\n",line_count,yytext);
}
"continue" {
    fprintf(f1,"<%s> ","CONTINUE");
    printf("Line no %d: Token <CONTINUE> Lexeme %s found\n\n",line_count,yytext);
}
"goto"     {
    fprintf(f1,"<%s> ","GOTO");
    printf("Line no %d: Token <GOTO> Lexeme %s found\n\n",line_count,yytext);
}
"long"     {
    fprintf(f1,"<%s> ","LONG");
    printf("Line no %d: Token <LONG> Lexeme %s found\n\n",line_count,yytext);
}
"short"    {
    fprintf(f1,"<%s> ","SHORT");
    printf("Line no %d: Token <SHORT> Lexeme %s found\n\n",line_count,yytext);
}
"static"   {
    fprintf(f1,"<%s> ","STATIC");
    printf("Line no %d: Token <STATIC> Lexeme %s found\n\n",line_count,yytext);
}
"unsigned" {
    fprintf(f1,"<%s> ","UNSIGNED");
    printf("Line no %d: Token <UNSIGNED> Lexeme %s found\n\n",line_count,yytext);
}


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
"\'" {
    BEGIN Char_const;
    str1="";
    str1 = str1+"\'";
}
<Char_const>"\n" {
    err_count++;
    printf("Error at line no %d: Unterminated character %s\n\n\n",line_count,str1.c_str());
    line_count++;
    BEGIN INITIAL;
}
<Char_const>"\'" {
    if(str1 == "\'"){
        err_count++;
        str1 = str1+"\'";
        printf("\nError at line no %d: Empty character constant error %s\n\n\n",line_count,str1.c_str());
    }
    else if(str1 == "\'\\"){
        err_count++;
        str1 = str1+"\'";
        printf("Error at line no %d: Unterminated character %s\n\n",line_count,str1.c_str());
    }
    else{
        str1 = str1+"\'";
        bool temp = print_char_constant(str1,line_count);
        if(temp){
            inserted = symboltable->insert(str1,"CONST_CHAR","");
            if(inserted.second.first == 0 && inserted.second.second == 0) symboltable->print_all_scope_nonempty_indices();
            else printf("< %s : CONST_CHAR > already exists in ScopeTable# %s at position %d, %d\n\n",yytext,inserted.first.c_str(),inserted.second.first,inserted.second.second);
        }
    }
    BEGIN INITIAL;
}
<Char_const>. {
    str1 = str1+yytext;
}


"++"    | 
"--" {
    fprintf(f1,"<INCOP, %s> ",yytext);
    printf("Line no %d: Token <INCOP> Lexeme %s found\n\n",line_count,yytext);
}
"+"     | 
"-" {
    fprintf(f1,"<ADDOP, %s> ",yytext);
    printf("Line no %d: Token <ADDOP> Lexeme %s found\n\n",line_count,yytext);
}
"*"      | 
"/"     | 
"%" {
    fprintf(f1,"<MULOP, %s> ",yytext);
    printf("Line no %d: Token <MULOP> Lexeme %s found\n\n",line_count,yytext);
}
"<="    | 
">="    | 
"=="    |   
"!=" {
    fprintf(f1,"<RELOP, %s> ",yytext);
    printf("Line no %d: Token <RELOP> Lexeme %s found\n\n",line_count,yytext);
}
"<"     | 
">"  {
    fprintf(f1,"<RELOP, %s> ",yytext);
    printf("Line no %d: Token <RELOP> Lexeme %s found\n\n",line_count,yytext);
}
"=" {
    fprintf(f1,"<ASSIGNOP, %s> ",yytext);
    printf("Line no %d: Token <ASSIGNOP> Lexeme %s found\n\n",line_count,yytext);
}
"!" {
    fprintf(f1,"<NOT, %s> ",yytext);
    printf("Line no %d: Token <NOT> Lexeme %s found\n\n",line_count,yytext);
}
"&&"    | 
"||" {
    fprintf(f1,"<LOGICOP, %s> ",yytext);
    printf("Line no %d: Token <LOGICOP> Lexeme %s found\n\n",line_count,yytext);
}
"(" {
    fprintf(f1,"<LPAREN, %s> ",yytext);
    printf("Line no %d: Token <LPAREN> Lexeme %s found\n\n",line_count,yytext);
}
")" {
    fprintf(f1,"<RPAREN, %s> ",yytext);
    printf("Line no %d: Token <RPAREN> Lexeme %s found\n\n",line_count,yytext);
}
"{" {
    symboltable->EnterScope();
    fprintf(f1,"<LCURL, %s> ",yytext);
    printf("Line no %d: Token <LCURL> Lexeme %s found\n\n",line_count,yytext);
}
"}" {
    symboltable->ExitScope();
    fprintf(f1,"<RCURL, %s> ",yytext);
    printf("Line no %d: Token <RCURL> Lexeme %s found\n\n",line_count,yytext);
}
"[" {
    fprintf(f1,"<LTHIRD, %s> ",yytext);
    printf("Line no %d: Token <LTHIRD> Lexeme %s found\n\n",line_count,yytext);
}
"]" {
    fprintf(f1,"<RTHIRD, %s> ",yytext);
    printf("Line no %d: Token <RTHIRD> Lexeme %s found\n\n",line_count,yytext);
}
"," {
    fprintf(f1,"<COMMA, %s> ",yytext);
    printf("Line no %d: Token <COMMA> Lexeme %s found\n\n",line_count,yytext);
}
";" {
    fprintf(f1,"<SEMICOLON, %s> ",yytext);
    printf("Line no %d: Token <SEMICOLON> Lexeme %s found\n\n",line_count,yytext);
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


"\"" {
    BEGIN String;
    initial_line = line_count;
    str1="";
    str2="";
    str1=str1+yytext;
}
<String>"\n" {
    err_count++;
    printf("Error at line no %d: Unterminated string %s\n\n",initial_line,str1.c_str());
    line_count++;
    str1="";
    str2="";
    BEGIN INITIAL;
}
<String>"\\\n" {
    line_count++;
    str1=str1+yytext;  
    str2=str2+""; 
}
<String>(\\)[nt'"afrbv0\\] {
    str1=str1+yytext;
    print_escape_sequence(yytext,str2);
}
<String>"\"" {
    str1=str1+yytext;
    fprintf(f1,"<STRING, %s> ",str2.c_str());
    printf("Line no %d: Token <STRING> Lexeme %s found --> <STRING, %s>\n\n",line_count,str1.c_str(),str2.c_str());
    BEGIN INITIAL;
}
<String><<EOF>> {
    err_count++;
    printf("Error at line no %d: Unterminated string %s\n\n",initial_line,str1.c_str());
    symboltable->print_all_scope_nonempty_indices();
    printf("Total lines: %d\n",line_count);
    printf("Total errors: %d\n",err_count);
    return 0;
}
<String>. {
    str1=str1+yytext;
    str2=str2+yytext;    
}


"//" {
    BEGIN Single_line_comment;
    cmnt = "";
    cmnt = cmnt+yytext;
}
<Single_line_comment>"\\\n" {
    line_count++;
    cmnt = cmnt+yytext;
}
<Single_line_comment>"\n" {
    printf("Line no %d: Token <COMMENT> Lexeme %s found\n\n",line_count,cmnt.c_str());
    line_count++;
    BEGIN INITIAL;
} 
<Single_line_comment>. {
    cmnt = cmnt+yytext;
}

"/*" {
    BEGIN Multi_line_comment;
    initial_line = line_count;
    cmnt = "";
    cmnt = cmnt+yytext;
}
<Multi_line_comment>"*/" {
    printf("Line no %d: Token <COMMENT> Lexeme %s*/ found\n\n",line_count,cmnt.c_str());
    BEGIN INITIAL;
}
<Multi_line_comment>"\n" {
    line_count++;
    cmnt = cmnt+yytext;
}
<Multi_line_comment>. {
    cmnt = cmnt+yytext;
}
<Multi_line_comment><<EOF>> {
    err_count++;
    printf("Error at line no %d: Unterminated comment %s\n\n",initial_line,cmnt.c_str());
    symboltable->print_all_scope_nonempty_indices();
    printf("Total lines: %d\n",line_count);
    printf("Total errors: %d\n",err_count);
    return 0;
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
    freopen("output_log.txt", "w", stdout);
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
    }

    yyin = input_file;
    yylex();
    fclose(yyin);
    fclose(f1);

    return 0;
}