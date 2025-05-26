%option noyywrap
%x VECTOR

%{
    #include<bits/stdc++.h>
    using namespace std;
    stack<char> st;
    int line_count=1;

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
<VECTOR>"int"   |
"float"         |
"double"        |
"char"          
<VECTOR>">" {
    if(st.empty()){
        cout<<"Line no. "<<line_count<<" Error in <VECTOR_TYPE> declaration\n";
        return 0;
    }
    st.pop();
    if(st.empty()){
        BEGIN INITIAL;
    }
}

"\n" {
    line_count++;
}

%%

int main()
{
    input_file = fopen("input.txt");
    yyin = input_file;
    yylex();

    return 0;
}