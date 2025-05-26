%option noyywrap

%{

#include<iostream>
using namespace std;


%}

lowercase [a-z]
uppercase [A-Z]
normalword {lowercase}+
camelword {uppercase}{lowercase}*

%%

{camelword}{camelword}    |
{normalword} {
    cout<<"camelCase1"<<endl;
    cout<<yytext<<endl;
    return 0;
}

("_")?({lowercase}+("_"))+ {
    cout<<"snake_case"<<endl;
    cout<<yytext<<endl;
    return 0;
}

"_" {
    cout<<"snake_case"<<endl;
    return 0;
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