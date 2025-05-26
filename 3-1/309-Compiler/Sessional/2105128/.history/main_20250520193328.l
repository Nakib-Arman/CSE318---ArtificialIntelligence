%option noyywrap
%x VECTOR
%x DISCARD

%{
    #include<bits/stdc++.h>
    using namespace std;
    stack<char> st;
    int line_count=1;
    string str="";
%}

ws ([ \v\t]*)

%%

"vector"{ws}?"<" {
    BEGIN VECTOR;
    st.push(yytext[0]);
    str+="vector<";
}

<VECTOR>"vector"{ws}?"<" {
    st.push(yytext[0]);
    str+="vector<";
}

<VECTOR>{ws} {}

<VECTOR>"int"{ws}?">"     |
<VECTOR>"float"{ws}?">"   |
<VECTOR>"double"{ws}?">"    |
<VECTOR>"char"{ws}?">" {
    if(st.empty()){
        cout<<"Line no. "<<line_count<<" Error in <VECTOR_TYPE> declaration\n";
        // cout<<"not matched1"<<endl;
        return 0;
    }
    st.pop();
    if(st.empty()){
        BEGIN INITIAL;
    }
    if(yytext[0] == 'i') str+="int>";
    if(yytext[0] == 'i') str+="int>";
    if(yytext[0] == 'i') str+="int>";
    if(yytext[0] == 'i') str+="int>";
}

<VECTOR>">" {
    if(st.empty()){
        cout<<"Line no. "<<line_count<<" Error in <VECTOR_TYPE> declaration\n";
        // cout<<"not matched2"<<endl;
        return 0;
    }
    st.pop();
    if(st.empty()){
        BEGIN INITIAL;
    }
}

<VECTOR>. {
    cout<<"not matched3"<<endl;
    return 0;
}

"\n" {
    cout<<"matched line: "<<line_count<<endl;
    line_count++;
}


<DISCARD>"\n" {
    line_count++;
    BEGIN INITIAL;
}

<DISCARD><<EOF>> {
    return 0;
}
<DISCARD>. {}

<<EOF>> {
    cout<<"matched line: "<<line_count<<endl;
    return 0;
}
. {
    cout<<"Line no. "<<line_count<<" Invalid input"<<endl;
    BEGIN DISCARD;
}

%%

int main()
{
    FILE *input_file = fopen("input.txt","r");
    yyin = input_file;
    yylex();

    return 0;
}