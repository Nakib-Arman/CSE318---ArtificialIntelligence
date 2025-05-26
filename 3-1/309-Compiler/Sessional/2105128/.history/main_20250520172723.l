%option noyywrap
%x VECTOR

%{
    #include<bits/stdc++.h>
    using namespace std;
    stack<char> st;

%}

ws ([ \v\t]*)

%%

"vector"{ws}?"<" {
    BEGIN VECTOR;
    st.push(yytext[0]);
}
<VECTOR>"vector"{ws}?"<" {
    st.push(yytext[0]);
}
<
<VECTOR>">" {
    if(st.empty())
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