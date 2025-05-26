%option noyywrap
%x PAREN
%x CURLY
%x SQUARE

%{
    #include<bits/stdc++.h>
    using namespace std;
    stack<char> st;

%}


%%




%%

int main()
{
    yyin = stdin;
    yylex();

    return 0;
}