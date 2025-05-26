%option noyywrap
%x VECTOR

%{
    #include<bits/stdc++.h>
    using namespace std;
    stack<char> st;

%}


%%

"vector"([ \v\t]*)?"<" {
    BEGIN VECTOR;
    st.push(yytext[0]);
    return 0;
}

<VECTOR>"vector"([ \v\t]*)?"<" {
    
}

"\n" {
    return 0;
}

%%

int main()
{
    yyin = stdin;
    yylex();

    return 0;
}