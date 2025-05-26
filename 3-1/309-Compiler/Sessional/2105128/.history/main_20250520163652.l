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

"(" {
    st.push(yytext[0]);
}
")" {
    if(st.empty()){
        
    }
}



%%

int main()
{
    yyin = stdin;
    yylex();

    return 0;
}