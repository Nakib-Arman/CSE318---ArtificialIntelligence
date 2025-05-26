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

<VECTOR>{ws} {}

<VECTOR>"int"{ws}?">"     |
        "float"{ws}?">"   |
        "double"{ws}?">"    |
        "char"{ws}?">" {
    if(st.empty()){
        // cout<<"Line no. "<<line_count<<" Error in <VECTOR_TYPE> declaration\n";
        cout<<"not matched1"<<endl;
        return 0;
    }
    st.pop();
    if(st.empty()){
        BEGIN INITIAL;
    }
}

">" {
    if(st.empty()){
        // cout<<"Line no. "<<line_count<<" Error in <VECTOR_TYPE> declaration\n";
        cout<<"not matched2"<<endl;
        return 0;
    }
    st.pop();
    if(st.empty()){
        BEGIN INITIAL;
    }
}

<VECTOR>. {
    cout<<yytext<<endl;
    cout<<"not matched3"<<endl;
    return 0;
}

"\n" {
    cout<<"matched line: "<<line_count<<endl;
    line_count++;
}

<<EOF>> {
    cout<<"matched line: "<<line_count<<endl;
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