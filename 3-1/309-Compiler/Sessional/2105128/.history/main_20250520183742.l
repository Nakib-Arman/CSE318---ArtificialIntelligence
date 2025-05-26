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

<VECTOR>"int"{ws}?   |
"float"{ws}?         |
{ws}?"double"{ws}?        |
{ws}?"char"{ws}? {}

<VECTOR>">" {
    if(st.empty()){
        // cout<<"Line no. "<<line_count<<" Error in <VECTOR_TYPE> declaration\n";
        cout<<"unmatched"<<endl;
        return 0;
    }
    st.pop();
    if(st.empty()){
        BEGIN INITIAL;
    }
}



<VECTOR>. {
    cout<<"not matched"<<endl;
    return 0;
}

"\n" {
    line_count++;
}

<<EOF>> {
    return 0;
}

%%

int main()
{
    FILE *input_file = fopen("input.txt","r");
    yyin = input_file;
    yylex();

    return 0;
}