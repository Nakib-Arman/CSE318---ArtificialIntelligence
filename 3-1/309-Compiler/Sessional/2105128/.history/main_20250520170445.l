%option noyywrap
%x VECTOR

%{
    #include<bits/stdc++.h>
    using namespace std;
    stack<char> st;

%}


%%

"vector" {
    BEGIN VECTOR;
}
<VECTOR>"<"

%%

int main()
{
    yyin = stdin;
    yylex();

    return 0;
}