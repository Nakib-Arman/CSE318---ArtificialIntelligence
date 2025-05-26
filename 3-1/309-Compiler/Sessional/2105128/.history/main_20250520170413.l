%option noyywrap
%x 

%{
    #include<bits/stdc++.h>
    using namespace std;
    stack<char> st;

%}


%%

"vector" {

}

%%

int main()
{
    yyin = stdin;
    yylex();

    return 0;
}